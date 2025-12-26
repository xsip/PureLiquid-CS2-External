#include <CS2/Interfaces/CGameTraceManager.h>
#include <CS2/SDK/C_CSPlayerPawn.h>
#include <CS2/Interfaces/Manager.h>
#include <CS2/Enums/TraceMasks.h>
#include <GlobalData/Include.h>
#include <CS2/Patterns.h>
using namespace Globals;


namespace CS2 {
#pragma code_seg(".traceShapeSeg")
#pragma optimize("", off)
#pragma runtime_checks("", off)
#pragma check_stack(off)  
	__declspec(safebuffers)
		DWORD WINAPI TraceShapeThread(LPVOID lpParam) {

		TraceShapeCtx* ctx = (TraceShapeCtx*)lpParam;

		ctx->TraceShape(ctx->pGameTraceManager, ctx->ray, ctx->vStartPos, ctx->vEndPos, ctx->pTraceFilter, ctx->pTrace);
		return 1;
	}

	DWORD WINAPI TraceShapeThreadEnd() { return 0; }
#pragma check_stack()  
#pragma runtime_checks("", restore) 
#pragma optimize("", on)
#pragma code_seg()

	bool CGameTraceManager::IsPlayerVisible(client::C_CSPlayerPawn* pLocal, client::C_CSPlayerPawn* pEnemy, bool bDebug) {

		if (pLastUsedPawn != pLocal) {
			pLastUsedPawn = pLocal;
			pLastUsedTraceShapeFilter = TraceFilter_t::InitEntitiesOnly(pLastUsedPawn, MASK_PLAYER_VISIBLE, 4);
		}

		if (!pLastUsedTraceShapeFilter)
			return {};

		if (!TraceShapeFn) {
			auto pClient = proc.GetRemoteModule("client.dll");
			if (!pClient) {
				printf("Error Finding client.dll!!\n");
				return {};
			}

			TraceShapeFn = reinterpret_cast<TraceShapeFnDef>(pClient->ScanMemory(TRACESHAPE_PATTERN));
			if (!TraceShapeFn) {
				printf("Error Finding TraceShape Function!!\n");
				return {};
			}

			printf("TraceShape Function: client.dll + 0x%p\n", reinterpret_cast<uintptr_t>(TraceShapeFn) - pClient->GetAddr());
		}



		pLastUsedTrace = reinterpret_cast<trace_t*>(proc.Alloc(sizeof(trace_t)));
		if (!pLastUsedTrace) {
			printf("Error allocating trace!!\n");
			return {};
		}

		if (!pLastUsedRay) {

			pLastUsedRay = reinterpret_cast<Ray_t*>(proc.Alloc(sizeof(Ray_t)));

			if (!pLastUsedRay) {
				printf("Error allocating ray!!\n");
				return {};
			}

			Ray_t ray{};
			if (!proc.Write<Ray_t>(reinterpret_cast<uintptr_t>(pLastUsedRay), ray)) {
				printf("Failed to write remote Ray_t!\n");
				return {};
			}
			printf("Allocated Ray: 0x%p\n", pLastUsedRay);
		}


		TraceShapeCtx ctx;
		ctx.ray = reinterpret_cast<Ray_t*>(pLastUsedRay);


		ctx.pGameTraceManager = this;
		ctx.pTrace = pLastUsedTrace;
		ctx.pTraceFilter = pLastUsedTraceShapeFilter;
		ctx.TraceShape = TraceShapeFn;
		ctx.vEndPos = pEnemy->m_vOldOrigin;
		ctx.vStartPos = (pLocal->m_vOldOrigin + pLocal->m_vecViewOffset);

		if (!pTraceShapeRemoteCtx) {
			pTraceShapeRemoteCtx = reinterpret_cast<TraceShapeCtx*>(proc.Alloc(sizeof(TraceShapeCtx)));
			if (!pTraceShapeRemoteCtx) {
				printf("Error Allocating TraceShapeRemoteCtx!!\n");
				return {};
			}
			printf("TraceShapeRemoteCtx: 0x%p\n", reinterpret_cast<uintptr_t>(pTraceShapeRemoteCtx));

		}

		if (!proc.Write<TraceShapeCtx>(reinterpret_cast<uintptr_t>(pTraceShapeRemoteCtx), ctx)) {
			printf("Failed to write update context!\n");
			return {};
		}
		if (!pTraceShapeShellcodeRemote) {
			pTraceShapeShellcodeRemote = proc.AllocAndWriteShellcode(TraceShapeThread, TraceShapeThreadEnd);
			if (!pTraceShapeShellcodeRemote) {
				printf("Failed to allocate TraceShape shellcode!\n");
				proc.FreeRemote(pTraceShapeRemoteCtx);
				return {};
			}

			printf("[+] TraceShape shellcode: 0x%p\n", pTraceShapeShellcodeRemote);
		}

		// printf("[+] Executing TraceShape thread...\n");

		// Execute using ExecuteAndCleanup
		HANDLE hThread = proc.CreateRemoteThreadEx(
			reinterpret_cast<LPTHREAD_START_ROUTINE>(pTraceShapeShellcodeRemote),
			pTraceShapeRemoteCtx
		);

		if (!hThread) {
			printf("Failed to create TraceShape thread!\n");
			proc.FreeRemote(pTraceShapeShellcodeRemote);
			proc.FreeRemote(pTraceShapeRemoteCtx);
			proc.FreeRemote(pLastUsedTrace);
			return {};
		}

		DWORD waitResult = WaitForSingleObject(hThread, 10000);

		if (waitResult != WAIT_OBJECT_0) {
			printf("TraceShape Thread wait failed or timed out! Result: %d\n", waitResult);
			CloseHandle(hThread);
			if (!bDebug) {
				proc.FreeRemote(pTraceShapeRemoteCtx);
				proc.FreeRemote(pTraceShapeShellcodeRemote);
			}
			return {};
		}

		DWORD exitCode = 0;
		GetExitCodeThread(hThread, &exitCode);
		CloseHandle(hThread);

		trace_t resultTrace;
		if (!proc.Read(reinterpret_cast<uintptr_t>(pLastUsedTrace), &resultTrace, sizeof(trace_t))) {
			printf("Failed to read result trace_t!\n");
			proc.FreeRemote(pTraceShapeRemoteCtx);
			proc.FreeRemote(pTraceShapeShellcodeRemote);
			return {};
		}

		// printf("[+] TraceData.fraction: %.3f\n", resultTrace.Fraction);

		return resultTrace.HitEntity == pEnemy || resultTrace.Fraction == 1.0f;

	}

#pragma code_seg(".initTraceFilterSeg")
#pragma optimize("", off)
#pragma runtime_checks("", off)
#pragma check_stack(off)  
	__declspec(safebuffers)
		DWORD WINAPI InitEntitiesOnlyThread(LPVOID lpParam) {
		InitEntityTraceFilterCtx* ctx = (InitEntityTraceFilterCtx*)lpParam;
		ctx->fn(ctx->filter, ctx->pSkipPawn, ctx->mask, ctx->layer, 15);
		return 1;
	}

	DWORD WINAPI InitEntitiesOnlyThreadEnd() { return 0; }
#pragma check_stack()  
#pragma runtime_checks("", restore) 
#pragma optimize("", on)
#pragma code_seg()

	TraceFilter_t* TraceFilter_t::InitEntitiesOnly(client::C_CSPlayerPawn* skip, uint32_t mask, int layer, bool bDebug)
	{
		auto pClient = proc.GetRemoteModule("client.dll");
		if (!pClient) {
			printf("Error Finding client.dll!!\n");
			return nullptr;
		}


		auto TraceFilterFn = reinterpret_cast<InitTraceFilterFn>(pClient->ScanMemory(INIT_TRACE_ENTITIES_ONLY_PATTERN));
		if (!TraceFilterFn) {
			printf("Error Finding TraceFilterFn Function!!\n");
			return nullptr;
		}

		
		auto pFilter = proc.Alloc(sizeof(TraceFilter_t));

		if (!pFilter) {
			printf("Error Allocating tracefilter!!\n");
			return nullptr;
		}


		InitEntityTraceFilterCtx ctx;
		ctx.filter = reinterpret_cast<TraceFilter_t*>(pFilter);
		ctx.fn = TraceFilterFn;
		ctx.layer = layer;
		ctx.mask = mask;
		ctx.pSkipPawn = skip;
		void* pRemoteCtx = proc.Alloc(sizeof(InitEntityTraceFilterCtx));

		if (!proc.Write<InitEntityTraceFilterCtx>(reinterpret_cast<uintptr_t>(pRemoteCtx), ctx)) {
			printf("Failed to write remote context for entity only tracefilter!!\n");
			return {};
		}


		printf("[+] Remote context: 0x%p\n", pRemoteCtx);

		void* shellcode = proc.AllocAndWriteShellcode(InitEntitiesOnlyThread, InitEntitiesOnlyThreadEnd);
		if (!shellcode) {
			printf("Failed to allocate InitEntitiesOnlyThread shellcode!\n");
			proc.FreeRemote(pRemoteCtx);
			return nullptr;
		}

		printf("[+] Remote shellcode: 0x%p\n", shellcode);
		printf("[+] Executing InitEntitiesOnlyThread thread...\n");

		// Execute using ExecuteAndCleanup
		HANDLE hThread = proc.CreateRemoteThreadEx(
			reinterpret_cast<LPTHREAD_START_ROUTINE>(shellcode),
			pRemoteCtx
		);

		if (!hThread) {
			printf("Failed to create remote thread!\n");
			proc.FreeRemote(shellcode);
			proc.FreeRemote(pRemoteCtx);
			return nullptr;
		}

		printf("[+] Waiting for thread completion...\n");
		DWORD waitResult = WaitForSingleObject(hThread, 10000);

		if (waitResult != WAIT_OBJECT_0) {
			printf("Thread wait failed or timed out! Result: %d\n", waitResult);
			CloseHandle(hThread);
			if (!bDebug) {
				proc.FreeRemote(shellcode);
				proc.FreeRemote(pRemoteCtx);
			}
			return nullptr;
		}

		DWORD exitCode = 0;
		GetExitCodeThread(hThread, &exitCode);
		CloseHandle(hThread);

		printf("[+] Thread returned exit code: %u\n", exitCode);

		printf("Create TraceFilter successfull!\n");
		return reinterpret_cast<TraceFilter_t*>(pFilter);


	}

}