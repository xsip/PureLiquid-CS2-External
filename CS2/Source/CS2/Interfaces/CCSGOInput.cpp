#include <CS2/Interfaces/CCSGOInput.h>
#include <CS2/Patterns.h>
#include <Math/Vector.h>
#include <GlobalData/Include.h>
using namespace Globals;

namespace CS2 {
    static void* g_pOriginalCreateMove = nullptr;
    static CreateMoveHookData* g_pHookData = nullptr;

#pragma code_seg(".createMoveHook")
#pragma optimize("", off)
#pragma runtime_checks("", off)
#pragma check_stack(off)  

    double __fastcall CCSGOInput::CreateMove_Hook_Shellcode(
        int64_t a1, unsigned int a2, CUserCmd* cmd)
    {
        CreateMoveHookData* data = g_pHookData;

        if (!data) {
            typedef double(__fastcall* CreateMoveFn)(int64_t, unsigned int, CUserCmd*);
            CreateMoveFn original = (CreateMoveFn)g_pOriginalCreateMove;
            return original(a1, a2, cmd);
        }
        

        if (data->bForceSubtickViewAngle) {
            data->bForceSubtickViewAngle = false;
            auto pHistoryBase = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(cmd) + 0x38);
            if (pHistoryBase) {
                auto pHistoryCountBase = *reinterpret_cast<uintptr_t*>(pHistoryBase);
                if (pHistoryCountBase) {
                    int pHistoryCount = *reinterpret_cast<int*>(pHistoryCountBase + +0x4);
                    if (pHistoryCount) {

                        for (int i = 1; i < pHistoryCount; i++) {
                            CSGOInputHistoryEntryPB* pHistoryEntry = *reinterpret_cast<CSGOInputHistoryEntryPB**>(pHistoryBase + (0x8 * i));
                            if (pHistoryEntry) {
                                if (pHistoryEntry->pViewCmd) {
                                    data->cmd = (uint64_t)cmd;

                                    pHistoryEntry->pViewCmd->angValue.x = data->vViewAnglesToSet.x;
                                    pHistoryEntry->pViewCmd->angValue.y = data->vViewAnglesToSet.y;
                                    pHistoryEntry->pViewCmd->angValue.z = data->vViewAnglesToSet.z;
                                    pHistoryEntry->cached_bits |= INPUT_HISTORY_BITS_VIEWANGLES;
                                }
                            }
                        }
                    }
                }
                if (cmd->csgoUserCmd.pBaseCmd && cmd->csgoUserCmd.pBaseCmd->pViewAngles) {
                    cmd->csgoUserCmd.pBaseCmd->pViewAngles->angValue.x = data->vViewAnglesToSet.x;
                    cmd->csgoUserCmd.pBaseCmd->pViewAngles->angValue.y = data->vViewAnglesToSet.y;
                    cmd->csgoUserCmd.pBaseCmd->pViewAngles->angValue.z = data->vViewAnglesToSet.z;

                }
            }
        }
        
        if (data->bForceBtn) {
            data->bForcedBtn = false;
            cmd->nButtons.nValue |= data->btnToForce;
            data->bForceBtn = false;
            data->btnToForce = 0;
            data->bForcedBtn = true;
        }



        // Call original
        typedef double(__fastcall* CreateMoveFn)(int64_t, unsigned int, CUserCmd*);
        CreateMoveFn original = (CreateMoveFn)g_pOriginalCreateMove;
        return original(a1, a2, cmd);
    }

    void CCSGOInput::CreateMove_Hook_Shellcode_End() {}

#pragma check_stack()  
#pragma runtime_checks("", restore) 
#pragma optimize("", on)
#pragma code_seg()

    uintptr_t CCSGOInput::FindCreateMove()
    {
        auto client = proc.GetRemoteModule("client.dll");
        if (!client || !client->IsValid()) {
            printf("[!] Failed to get client.dll\n");
            return 0;
        }

        // Pattern for CreateMove function
        const char* pattern = "48 8B C4 4C 89 40 ?? 48 89 48 ?? 55 53 41 54";

        uint8_t* addr = client->ScanMemory(pattern);
        if (!addr) {
            printf("[!] Failed to find CreateMove pattern\n");
            return 0;
        }

        uintptr_t createMoveAddr = reinterpret_cast<uintptr_t>(addr);
        printf("[+] Found CreateMove at: client.dll + 0x%llX\n",
            createMoveAddr - client->GetAddr());

        return createMoveAddr;
    }



    bool CCSGOInput::HookCreateMove()
    {

        auto client = proc.GetRemoteModule("client.dll");
        if (!client || !client->IsValid()) {
            printf("[!] Failed to get client.dll\n");
            return -1;
        }

        uintptr_t instanceAddr = reinterpret_cast<uintptr_t>(this);
        if (m_bIsHooked) {
            printf("[!] Hook already installed\n");
            return false;
        }

        if (!instanceAddr) {
            printf("[!] Invalid CCSGOInput instance address\n");
            return false;
        }

        printf("[+] CCSGOInput instance: 0x%llX\n", instanceAddr);

        // Find CreateMove function
        uintptr_t createMoveFunc = FindCreateMove();
        if (!createMoveFunc) {
            return false;
        }

 
 

        auto res = client->FindVTableContainingFunction(createMoveFunc);

        if (!res.vTableAddr) {
            printf("Error finding VTalbe for CCSGOInput!\n");
            return false;
        }

        // Calculate VTable entry address
        int CREATE_MOVE_INDEX = res.index;

        if (CREATE_MOVE_INDEX < 0) {
            printf("ERROR FINDING CREATE MOVE INDEX!!\n");
            return false;
        }

        m_pTargetFunction = res.vTableAddr + (CREATE_MOVE_INDEX * 8);

        printf("[+] VTable address: 0x%llX\n", res.vTableAddr);
        printf("[+] CreateMove VTable entry: 0x%llX\n", m_pTargetFunction);

        // Read original function pointer
        uint64_t originalFunc = proc.ReadDirect<uint64_t>(m_pTargetFunction);
        g_pOriginalCreateMove = reinterpret_cast<void*>(originalFunc);

        printf("[+] Original CreateMove: 0x%llX\n", originalFunc);

        // Allocate remote data
        m_pDataRemote = proc.Alloc(sizeof(CreateMoveHookData));
        if (!m_pDataRemote) {
            printf("[!] Failed to allocate CreateMoveHookData\n");
            return false;
        }
        printf("[+] Remote CreateMoveHookData: 0x%p\n", m_pDataRemote);

        // Initialize hook data
        CreateMoveHookData data{};
        data.originalFunc = originalFunc;
        data.cmd = 0;
        data.bForceBtn = false;
        data.bForcedBtn = true;
        data.btnToForce = IN_JUMP;

        data.bForceSubtickViewAngle = false;
        data.vViewAnglesToSet = { 0.0f,0.0f,0.0f };

        proc.Write<CreateMoveHookData>(reinterpret_cast<uintptr_t>(m_pDataRemote), data);

        // Copy hook shellcode to remote process
        size_t shellcodeSize = reinterpret_cast<uintptr_t>(CreateMove_Hook_Shellcode_End) -
            reinterpret_cast<uintptr_t>(CreateMove_Hook_Shellcode);

        m_pShellcodeRemote = proc.Alloc(shellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (!m_pShellcodeRemote) {
            printf("[!] Failed to allocate shellcode memory\n");
            return false;
        }

        std::vector<uint8_t> localCode(shellcodeSize);
        memcpy(localCode.data(), CreateMove_Hook_Shellcode, shellcodeSize);

        if (!proc.WriteArray(reinterpret_cast<uintptr_t>(m_pShellcodeRemote), localCode)) {
            printf("[!] Failed to write shellcode\n");
            return false;
        }

        printf("[+] Remote shellcode: 0x%p (size: %zu bytes)\n", m_pShellcodeRemote, shellcodeSize);

        // ================================================================
        // CRITICAL FIX: Allocate storage for global pointers FIRST
        // ================================================================

        // Allocate storage for g_pHookData pointer
        void* pHookDataStorage = proc.Alloc(8);
        if (!pHookDataStorage) {
            printf("[!] Failed to allocate hook data storage\n");
            return false;
        }

        // Write the address of remote data to storage
        if (!proc.Write<uint64_t>(reinterpret_cast<uintptr_t>(pHookDataStorage),
            reinterpret_cast<uint64_t>(m_pDataRemote))) {
            printf("[!] Failed to write hook data pointer\n");
            return false;
        }

        printf("[+] g_pHookData storage: 0x%p -> 0x%p\n", pHookDataStorage, m_pDataRemote);

        // Allocate storage for g_pOriginalCreateMove pointer
        void* pOrigPtrStorage = proc.Alloc(8);
        if (!pOrigPtrStorage) {
            printf("[!] Failed to allocate orig pointer storage\n");
            return false;
        }

        // Write original function address to storage
        if (!proc.Write<uint64_t>(reinterpret_cast<uintptr_t>(pOrigPtrStorage), originalFunc)) {
            printf("[!] Failed to write original pointer\n");
            return false;
        }

        printf("[+] g_pOriginalCreateMove storage: 0x%p -> 0x%llX\n", pOrigPtrStorage, originalFunc);

        // ================================================================
        // Patch RIP-relative instructions
        // ================================================================

        printf("[*] Patching RIP-relative instructions...\n");

        int ripLoadCount = 0;
        int patchedCount = 0;

        for (size_t i = 0; i < shellcodeSize - 7; i++) {
            // Look for: mov reg, [rip+disp32] (48 8B 05 ?? ?? ?? ??)
            if (localCode[i] == 0x48 && localCode[i + 1] == 0x8B && localCode[i + 2] == 0x05) {
                ripLoadCount++;

                uintptr_t instructionAddr = reinterpret_cast<uintptr_t>(m_pShellcodeRemote) + i;
                uintptr_t targetAddr;
                const char* varName;

                // First RIP load is g_pHookData
                if (ripLoadCount == 1) {
                    targetAddr = reinterpret_cast<uintptr_t>(pHookDataStorage);
                    varName = "g_pHookData";
                }
                // Subsequent RIP loads are g_pOriginalCreateMove
                else {
                    targetAddr = reinterpret_cast<uintptr_t>(pOrigPtrStorage);
                    varName = "g_pOriginalCreateMove";
                }

                // Calculate new RIP-relative offset
                // offset = target - (instruction_addr + instruction_size)
                int32_t newOffset = static_cast<int32_t>(targetAddr - (instructionAddr + 7));

                // Patch the offset in the shellcode
                if (!proc.Write<int32_t>(instructionAddr + 3, newOffset)) {
                    printf("[!] Failed to patch RIP offset at 0x%zX\n", i);
                    return false;
                }

                printf("[+] Patched RIP-relative %s at offset 0x%zX (target: 0x%p, offset: 0x%X)\n",
                    varName, i, (void*)targetAddr, newOffset);

                patchedCount++;
            }
        }

        if (patchedCount == 0) {
            printf("[!] ERROR: No RIP-relative instructions found in shellcode!\n");
            printf("[!] This means the shellcode structure is different than expected.\n");
            return false;
        }

        printf("[+] Successfully patched %d RIP-relative instruction(s)\n", patchedCount);

        // ================================================================
        // Install VTable hook
        // ================================================================

        printf("[*] Installing VTable hook...\n");

        DWORD oldProtect;
        if (!VirtualProtectEx(proc.m_hProc, reinterpret_cast<void*>(m_pTargetFunction),
            8, PAGE_READWRITE, &oldProtect)) {
            printf("[!] VirtualProtectEx failed: %d\n", GetLastError());
            return false;
        }

        if (!proc.Write<uint64_t>(m_pTargetFunction, reinterpret_cast<uint64_t>(m_pShellcodeRemote))) {
            printf("[!] Failed to write hook to VTable\n");
            VirtualProtectEx(proc.m_hProc, reinterpret_cast<void*>(m_pTargetFunction),
                8, oldProtect, &oldProtect);
            return false;
        }

        VirtualProtectEx(proc.m_hProc, reinterpret_cast<void*>(m_pTargetFunction),
            8, oldProtect, &oldProtect);

        m_bIsHooked = true;
        printf("[+] CreateMove VTable hook installed successfully!\n\n");

        return true;
    }

    bool CCSGOInput::UnhookCreateMove()
    {
        if (!m_bIsHooked) {
            printf("[!] Hook not installed\n");
            return false;
        }

        printf("[*] Uninstalling CreateMove VTable hook...\n");

        uint64_t originalFunc = reinterpret_cast<uint64_t>(g_pOriginalCreateMove);

        DWORD oldProtect;
        if (!VirtualProtectEx(proc.m_hProc, reinterpret_cast<void*>(m_pTargetFunction),
            8, PAGE_READWRITE, &oldProtect)) {
            printf("[!] VirtualProtectEx failed: %d\n", GetLastError());
            return false;
        }

        if (!proc.Write<uint64_t>(m_pTargetFunction, originalFunc)) {
            printf("[!] Failed to restore VTable entry\n");
            VirtualProtectEx(proc.m_hProc, reinterpret_cast<void*>(m_pTargetFunction),
                8, oldProtect, &oldProtect);
            return false;
        }

        VirtualProtectEx(proc.m_hProc, reinterpret_cast<void*>(m_pTargetFunction),
            8, oldProtect, &oldProtect);

        printf("[+] CreateMove VTable hook uninstalled\n");

        m_bIsHooked = false;

        return true;
    }

    void CCSGOInput::ForceButton(ECommandButtons btn)
    {
        if (!m_pDataRemote)
            return;
        proc.Write<bool>(reinterpret_cast<uintptr_t>(m_pDataRemote) +
            offsetof(CreateMoveHookData, bForceBtn), true);
        proc.Write<uint64_t>(reinterpret_cast<uintptr_t>(m_pDataRemote) +
            offsetof(CreateMoveHookData, btnToForce), static_cast<uint64_t>(btn));

        proc.Write<bool>(reinterpret_cast<uintptr_t>(m_pDataRemote) +
            offsetof(CreateMoveHookData, bForceBtn), true);

        // printf("[+] Queued button force: 0x%llX\n", static_cast<uint64_t>(btn));
    }

    void CCSGOInput::Attack(){
        ForceButton(IN_ATTACK);
    }

    void CCSGOInput::SetSubTickAngle(Vector vAngle) {
        if (!m_pDataRemote)
            return;
        proc.Write<Vector>(reinterpret_cast<uintptr_t>(m_pDataRemote) +
            offsetof(CreateMoveHookData, vViewAnglesToSet), vAngle);

        proc.Write<bool>(reinterpret_cast<uintptr_t>(m_pDataRemote) +
            offsetof(CreateMoveHookData, bForceSubtickViewAngle), true);
    }

    CreateMoveHookData CCSGOInput::GetExecutionData()
    {
        CreateMoveHookData data{};
        if (m_pDataRemote) {
            proc.Read(reinterpret_cast<uintptr_t>(m_pDataRemote), &data, sizeof(CreateMoveHookData));
        }
        return data;
    }

    uintptr_t CCSGOInput::ResolveViewAnglesOffset() {
        if (!pViewAnglesOffset) {
            auto hClient = ::Globals::proc.GetRemoteModule("client.dll");
            if (!hClient || hClient && !hClient->GetAddr()) {
                return NULL;
            }
            auto pViewAngleOffsetDisp = hClient->ScanMemory(C_CSGO_INPUT_VIEW_ANGLES_PATTERN);
            pViewAnglesOffset = hClient->ResolveDisp32(pViewAngleOffsetDisp, 3);
            if (!pViewAnglesOffset)
                return NULL;
        }

        return pViewAnglesOffset;
    }
}