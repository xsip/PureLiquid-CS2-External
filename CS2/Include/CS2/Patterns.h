#pragma once


// client.dll => @xref "Attempting to get hit box list and transforms for an uninitialized model"
/*
text:0000000000763044 48 8D 15 35 8F EF 00                    lea     rdx, aAttemptingToGe ; "Attempting to get hit box list and tran"...
.text:000000000076304B 48 8D 0D D6 8E EF 00                    lea     rcx, off_165BF28 ; "C:\\buildworker\\csgo_rel_win64\\build"...
.text:0000000000763052 89 05 B4 3C 6C 01                       mov     cs:dword_1E26D0C, eax
.text:0000000000763058 FF 15 1A D9 D7 00                       call    cs:?Assert_ConditionFailed@@YA_NAEBU_AssertCompileTimeConstantStruct_t@@PEBDZZ ; Assert_ConditionFailed(_AssertCompileTimeConstantStruct_t const &,char const *,...)
.text:000000000076305E 84 C0                                   test    al, al
.text:0000000000763060 74 01                                   jz      short loc_763063
.text:0000000000763062 CC                                      int     3               ; Trap to Debugger
.text:0000000000763063
.text:0000000000763063                         loc_763063:                             ; CODE XREF: sub_762FF0+21↑j
.text:0000000000763063                                                                 ; sub_762FF0+50↑j ...
.text:0000000000763063 32 C0                                   xor     al, al
.text:0000000000763065
.text:0000000000763065                         loc_763065:                             ; CODE XREF: sub_762FF0+B7↓j
.text:0000000000763065                                                                 ; sub_762FF0+238↓j
.text:0000000000763065 48 8B 9C 24 C0 00 00 00                 mov     rbx, [rsp+0A8h+arg_10]
.text:000000000076306D 48 81 C4 80 00 00 00                    add     rsp, 80h
.text:0000000000763074 41 5F                                   pop     r15
.text:0000000000763076 41 5D                                   pop     r13
.text:0000000000763078 5F                                      pop     rdi
.text:0000000000763079 5E                                      pop     rsi
.text:000000000076307A 5D                                      pop     rbp
.text:000000000076307B C3                                      retn
.text:000000000076307C                         ; ---------------------------------------------------------------------------
.text:000000000076307C
.text:000000000076307C                         loc_76307C:                             ; CODE XREF: sub_762FF0+45↑j
.text:000000000076307C BA 00 01 00 00                          mov     edx, 100h
.text:0000000000763081
.text:0000000000763081                         loc_763081:                             ; DATA XREF: .rdata:00000000019ECB84↓o
.text:0000000000763081                                                                 ; .rdata:00000000019ECB94↓o ...
.text:0000000000763081 4C 89 A4 24 B0 00 00 00                 mov     [rsp+0A8h+arg_0], r12
.text:0000000000763089 48 8B CB                                mov     rcx, rbx
.text:000000000076308C E8 DF 08 FF FF                          call    sub_753970
.text:0000000000763091 4C 8B A3 10 02 00 00                    mov     r12, [rbx+210h] ; bone matrix Pointer
*/
#define BONES_PTR_OFFSET_PATTERN "4C 8B A3 ?? ?? ?? ?? 4D 85 E4"



// @client.dll - i also posted about this on UC: https://www.unknowncheats.me/forum/counter-strike-2-a/733064-easy-silent-aim.html
/*

        .rdata:00000000015E4990                         ; const CSGOInterpolationInfoPB_CL::`vftable'
.rdata:00000000015E4990 F0 17 54 00 00 00 00 00 ??_7CSGOInterpolationInfoPB_CL@@6B@ dq offset sub_5417F0
.rdata:00000000015E4990                                                                 ; DATA XREF: sub_5417F0+F↑o
.rdata:00000000015E4990                                                                 ; sub_543CC0+15↑o ...
.rdata:00000000015E4998 A0 00 E1 00 00 00 00 00                 dq offset sub_E100A0
.rdata:00000000015E49A0 40 15 54 00 00 00 00 00                 dq offset sub_541540
.rdata:00000000015E49A8 80 15 54 00 00 00 00 00                 dq offset sub_541580
.rdata:00000000015E49B0 A0 15 54 00 00 00 00 00                 dq offset sub_5415A0
.rdata:00000000015E49B8 D0 00 E1 00 00 00 00 00                 dq offset sub_E100D0
.rdata:00000000015E49C0 00 F5 E0 00 00 00 00 00                 dq offset sub_E0F500
.rdata:00000000015E49C8 B0 15 54 00 00 00 00 00                 dq offset sub_5415B0
.rdata:00000000015E49D0 80 17 54 00 00 00 00 00                 dq offset sub_541780
.rdata:00000000015E49D8 D0 15 54 00 00 00 00 00                 dq offset sub_5415D0
.rdata:00000000015E49E0 50 B4 13 00 00 00 00 00                 dq offset nullsub_1385
.rdata:00000000015E49E8 10 17 54 00 00 00 00 00                 dq offset sub_541710
.rdata:00000000015E49F0 F0 05 E1 00 00 00 00 00                 dq offset sub_E105F0
.rdata:00000000015E49F8 10 0D E1 00 00 00 00 00                 dq offset sub_E10D10
.rdata:00000000015E4A00 90 17 54 00 00 00 00 00                 dq offset sub_541790
.rdata:00000000015E4A08 B0 17 54 00 00 00 00 00                 dq offset sub_5417B0
.rdata:00000000015E4A10 A0 17 54 00 00 00 00 00                 dq offset sub_5417A0
.rdata:00000000015E4A18 C0 F8 E0 00 00 00 00 00 off_15E4A18     dq offset sub_E0F8C0    ; DATA XREF: sub_542CE0↑o
.rdata:00000000015E4A20 90 18 54 00 00 00 00 00                 dq offset SetServerAngle_Interpolation_sub_541890 <= This function

SetServerAngle_Interpolation_sub_541890 + 0x7E
.text:000000000054190E E8 FD 44 F3 FF                          call    SetServerAngle_sub_475E10 <= Patch This call!!



Also found in VTable:
data:00000000015AE520                         ; const CUserMessage_Diagnostic_Response_Diagnostic::`vftable'
.rdata:00000000015AE520 60 61 47 00 00 00 00 00 ??_7CUserMessage_Diagnostic_Response_Diagnostic@@6B@ dq offset sub_476160
.rdata:00000000015AE520                                                                 ; DATA XREF: sub_476160+F↑o
.rdata:00000000015AE520                                                                 ; sub_4CAD60+51↑o ...
.rdata:00000000015AE528 A0 00 E1 00 00 00 00 00                 dq offset sub_E100A0
.rdata:00000000015AE530 10 21 47 00 00 00 00 00                 dq offset sub_472110
.rdata:00000000015AE538 F0 22 47 00 00 00 00 00                 dq offset sub_4722F0
.rdata:00000000015AE540 B0 23 47 00 00 00 00 00                 dq offset sub_4723B0
.rdata:00000000015AE548 D0 00 E1 00 00 00 00 00                 dq offset sub_E100D0
.rdata:00000000015AE550 00 F5 E0 00 00 00 00 00                 dq offset sub_E0F500
.rdata:00000000015AE558 D0 25 47 00 00 00 00 00                 dq offset sub_4725D0
.rdata:00000000015AE560 B0 3B 47 00 00 00 00 00                 dq offset sub_473BB0
.rdata:00000000015AE568 60 2C 47 00 00 00 00 00                 dq offset sub_472C60
.rdata:00000000015AE570 50 B4 13 00 00 00 00 00                 dq offset nullsub_1385
.rdata:00000000015AE578 60 36 47 00 00 00 00 00                 dq offset sub_473660
.rdata:00000000015AE580 F0 05 E1 00 00 00 00 00                 dq offset sub_E105F0
.rdata:00000000015AE588 10 0D E1 00 00 00 00 00                 dq offset sub_E10D10
.rdata:00000000015AE590 90 3D 47 00 00 00 00 00                 dq offset sub_473D90
.rdata:00000000015AE598 00 3F 47 00 00 00 00 00                 dq offset sub_473F00
.rdata:00000000015AE5A0 F0 3E 47 00 00 00 00 00                 dq offset sub_473EF0
.rdata:00000000015AE5A8 C0 F8 E0 00 00 00 00 00 off_15AE5A8     dq offset sub_E0F8C0    ; DATA XREF: sub_476220↑o
.rdata:00000000015AE5B0 10 5E 47 00 00 00 00 00                 dq offset SetServerAngle_sub_475E10 <= This
        */
#define SET_SERVER_ANGLE_CALLSITE_PATTERN "E8 ?? ?? ?? ?? 40 F6 C6 ?? 74 ?? 83 0F ?? 48 8B 43"

// client.dll => CClientInput @ Index 7
// text:0000000000821DB4 89 86 B8 06 00 00                       mov     [rsi+6B8h], eax
#define C_CSGO_INPUT_VIEW_ANGLES_PATTERN "F2 0F 11 86 ?? ?? ?? ?? 89 86 ?? ?? ?? ?? C7 86"


// @xref => models/inventory_items/dogtags.vmdl @ client.dll
#define CHANGE_MODEL_PATTERN "40 53 48 83 EC ?? 48 8B D9 4C 8B C2 48 8B 0D ?? ?? ?? ?? 48 8D 54 24"


// @xref => Physics/TraceShape - client.dll
#define TRACESHAPE_PATTERN "48 89 5C 24 ?? 48 89 4C 24 ?? 55 57"




// client @xref =>  [%d] Could not find Hud Element: %s\n
#define CCSGO_HUD_PATTERN "48 8B 05 ?? ?? ?? ?? 48 8B D9 48 85 C0 0F 84 ?? ?? ?? ?? 49 89 5B"

// client.dll =>
// .text:0000000000200C59 C6 44 24 20 0F								mov[rsp + 38h + var_18], 0Fh
// .text : 0000000000200C5E E8 3D 0C 00 00								call    TraceInitEntitiesOnly_sub_2018A0
// .text : 0000000000200C63 48 81 4B 10 00 00 0C 00						or qword ptr[rbx + 10h], 0C0000h
// .text : 0000000000200C6B 48 8D 05 7E 3A 33 01						lea     rax, ? ? _7CAnimGraphTraceFilter@@6B@; const CAnimGraphTraceFilter::`vftable'
#define INIT_TRACE_ENTITIES_ONLY_PATTERN "48 89 5C 24 ?? 48 89 74 24 ?? 57 48 83 EC ?? 0F B6 41 ?? 33 FF 24"



// Interfaces @ client.dll
#define C_CSGO_INPUT_PATTERN "48 8B 0D ?? ?? ?? ?? 4C 8D 47 14"
#define C_GAME_TRACE_MANAGER_PATTERN "4C 8B 2D ? ? ? ? 24"



// materialsystem.dll =>
// rdata:000000000012A188; class CMaterialSystem2 : CTier2AppSystem<IMaterialSystem2, 0>, CTier1AppSystem<IMaterialSystem2, 0>, CTier0AppSystem<IMaterialSystem2, 0>, CBaseAppSystem<IMaterialSystem2>, IMaterialSystem2, IAppSystem;  (#classinformer)
// .rdata:000000000012A188                 dq offset ? ? _R4CMaterialSystem2@@6B@; const CMaterialSystem2::`RTTI Complete Object Locator'
// .rdata:000000000012A190; const CMaterialSystem2::`vftable'
// .rdata:000000000012A190 ? ? _7CMaterialSystem2@@6B@ dq offset sub_38140
// .rdata:000000000012A190; DATA XREF : sub_36090 + 15↑o
// .rdata : 000000000012A190; sub_364D0 + B↑o
// .rdata:000000000012A198                 dq offset sub_381B0
// .rdata : 000000000012A1A0                 dq offset antlr3dfaspecialTransition
// .rdata : 000000000012A1A8                 dq offset sub_36A80
// .rdata : 000000000012A1B0                 dq offset sub_37F20
// .rdata : 000000000012A1B8                 dq offset sub_37F10
// .rdata : 000000000012A1C0                 dq offset sub_36080
// .rdata : 000000000012A1C8                 dq offset sub_44EE0
// .rdata : 000000000012A1D0                 dq offset sub_44EF0
// .rdata : 000000000012A1D8                 dq offset sub_34810
// .rdata : 000000000012A1E0                 dq offset sub_44EE0
// .rdata : 000000000012A1E8                 dq offset sub_381F0
// .rdata : 000000000012A1F0                 dq offset sub_38450
// .rdata : 000000000012A1F8                 dq offset sub_38460
// .rdata : 000000000012A200                 dq offset sub_38470
// .rdata : 000000000012A208                 dq offset sub_38540
// .rdata : 000000000012A210                 dq offset sub_38520
// .rdata : 000000000012A218                 dq offset sub_386B0
// .rdata : 000000000012A220                 dq offset sub_38760
// .rdata : 000000000012A228                 dq offset sub_38780
// .rdata : 000000000012A230                 dq offset sub_3B600
// .rdata : 000000000012A238                 dq offset sub_392B0
// .rdata : 000000000012A240                 dq offset sub_38120
// .rdata : 000000000012A248                 dq offset sub_3C9D0
// .rdata : 000000000012A250                 dq offset sub_3CC00
// .rdata : 000000000012A258                 dq offset sub_3CD30
// .rdata : 000000000012A260                 dq offset sub_3B9A0
// .rdata : 000000000012A268                 dq offset sub_3B9B0
// .rdata : 000000000012A270                 dq offset sub_3BFA0
// .rdata : 000000000012A278                 dq offset CreateMaterial_sub_3BE30 <= this
// .rdata : 000000000012A280                 dq offset sub_3BC30
/*

text:000000000003BE30                 mov     [rsp+arg_0], rbx
.text:000000000003BE35                 mov     [rsp+arg_10], rbp
.text:000000000003BE3A                 push    rsi
.text:000000000003BE3B                 push    rdi
.text:000000000003BE3C                 push    r14
.text:000000000003BE3E                 sub     rsp, 110h
.text:000000000003BE45                 mov     rax, cs:g_pMemAlloc
.text:000000000003BE4C                 mov     rsi, rdx
.text:000000000003BE4F                 mov     edx, 690h
.text:000000000003BE54                 mov     r14, r9
.text:000000000003BE57                 mov     rbp, r8
.text:000000000003BE5A                 mov     rcx, [rax]
.text:000000000003BE5D                 mov     rax, [rcx]
.text:000000000003BE60                 call    qword ptr [rax+8]
.text:000000000003BE63                 xor     edi, edi
.text:000000000003BE65                 mov     rbx, rax
.text:000000000003BE68                 test    rax, rax
.text:000000000003BE6B                 jz      short loc_3BEE1
.text:000000000003BE6D                 and     byte ptr [rbx+0Bh], 0C0h
.text:000000000003BE71                 lea     rax, ??_7CMaterial2@@6B@ ; const CMaterial2::`vftable' <= First function containing CMaterial2 VTable
.text:000000000003BE78                 mov     [rbx], rax
.text:000000000003BE7B                 mov     eax, 1
.text:000000000003BE80                 mov     dword ptr [rbx+0Ch], 0FFFFFFFFh
*/
#define CREATE_MATERIAL_FN_PATTERN "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 56 48 81 EC 10 01 00 00 48 8B 05 ?? ?? ?? ?? 48"


// tier0.dll => exported function.
#define LOAD_KV3_PROC_ADDRESS "?LoadKV3@@YA_NPEAVKeyValues3@@PEAVCUtlString@@PEBDAEBUKV3ID_t@@2I@Z"

// client.dll
#define GET_VIEW_MATRIX_FN "48 63 C1 48 8D 0D ?? ?? ?? ?? 48 C1 E0 06"

// scenesystem.dll =>
// .rdata:0000000000593D28                         ; class CAnimatableSceneObjectDesc: CBaseSceneObjectDesc, ISceneObjectDesc;  (#classinformer)
// .rdata:0000000000593D28 D0 34 5B 00 00 00 00 00                 dq offset ??_R4CAnimatableSceneObjectDesc@@6B@ ; const CAnimatableSceneObjectDesc::`RTTI Complete Object Locator'
// .rdata:0000000000593D30                         ; const VCAnimatableSceneObjectDesc::`vftable'
// .rdata:0000000000593D30 20 C7 04 00 00 00 00 00 ??_7VCAnimatableSceneObjectDesc@@6B@ dq offset sub_4C720
// .rdata:0000000000593D30                                                                 ; DATA XREF: .data:off_61B2F0↓o
// .rdata:0000000000593D38 A0 DF 04 00 00 00 00 00                 dq offset RenderAnimatable_Objects_sub_4DFA0 <= This function

#define CANIMATABLE_SCENE_OBJECT_DESC_RENDER_FN_PATTERN "48 8B C4 53 57 41 54 48 81 EC ?? ?? ?? ?? 49 63 F9 49"

// @ panorama.dll => xref CUIEngine::RunScript (compile+run)
#define RUN_SCRIPT_PATTERN "48 89 5C 24 18 4C 89 4C 24 20 48 89 54 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 80"




// @client.dll
/*

text:0000000000BF1DB7 48 8D 15 FA 4E EE 00                    lea     rdx, aSfuiNoticeDmBu_2 ; "#SFUI_Notice_DM_BuyMenu_RandomOFF"
.text:0000000000BF1DBE
.text:0000000000BF1DBE                         loc_BF1DBE:                             ; CODE XREF: sub_BF1850+446↑j
.text:0000000000BF1DBE                                                                 ; sub_BF1850+45C↑j
.text:0000000000BF1DBE 41 FF 50 78                             call    qword ptr [r8+78h]
.text:0000000000BF1DC2 4C 89 74 24 38                          mov     qword ptr [rsp+580h+var_548], r14
.text:0000000000BF1DC7 48 8D 8D A0 04 00 00                    lea     rcx, [rbp+480h+arg_10]
.text:0000000000BF1DCE 48 89 4C 24 30                          mov     [rsp+580h+var_550], rcx
.text:0000000000BF1DD3 48 8D 55 20                             lea     rdx, [rbp+480h+var_460]
.text:0000000000BF1DD7 48 8B 0D EA 78 92 01                    mov     rcx, cs:qword_25196C8
.text:0000000000BF1DDE 4C 8B C8                                mov     r9, rax
.text:0000000000BF1DE1 48 89 5C 24 28                          mov     [rsp+580h+var_558], rbx
.text:0000000000BF1DE6 41 B8 00 04 00 00                       mov     r8d, 400h
.text:0000000000BF1DEC C7 44 24 20 03 00 00 00                 mov     dword ptr [rsp+580h+var_560], 3
.text:0000000000BF1DF4 41 FF D7                                call    r15
.text:0000000000BF1DF7
.text:0000000000BF1DF7                         loc_BF1DF7:                             ; CODE XREF: sub_BF1850+520↑j
.text:0000000000BF1DF7 BA 01 80 00 00                          mov     edx, 8001h
.text:0000000000BF1DFC 48 8D 4D 20                             lea     rcx, [rbp+480h+var_460]
.text:0000000000BF1E00 E8 AB 35 1F 00                          call    sub_DE53B0
.text:0000000000BF1E05 F3 0F 10 87 70 3D 00 00                 movss   xmm0, dword ptr [rdi+3D70h]
.text:0000000000BF1E0D 48 8D 4C 24 50                          lea     rcx, [rsp+580h+var_530]
.text:0000000000BF1E12 33 D2                                   xor     edx, edx
.text:0000000000BF1E14 F3 0F 11 87 78 3D 00 00                 movss   dword ptr [rdi+3D78h], xmm0
.text:0000000000BF1E1C FF 15 F6 FA D0 00                       call    cs:?Purge@CBufferString@@QEAAXH@Z ; CBufferString::Purge(int)
.text:0000000000BF1E22 33 D2                                   xor     edx, edx
.text:0000000000BF1E24 48 8D 4D B0                             lea     rcx, [rbp+480h+var_4D0]
.text:0000000000BF1E28 FF 15 EA FA D0 00                       call    cs:?Purge@CBufferString@@QEAAXH@Z ; CBufferString::Purge(int)
.text:0000000000BF1E2E 4C 8B BC 24 50 05 00 00                 mov     r15, [rsp+580h+var_30]
.text:0000000000BF1E36
.text:0000000000BF1E36                         loc_BF1E36:                             ; CODE XREF: sub_BF1850+25A↑j
.text:0000000000BF1E36                                                                 ; DATA XREF: .pdata:00000000025B4A70↓o ...
.text:0000000000BF1E36 48 8D 4D F0                             lea     rcx, [rbp+480h+var_490]
.text:0000000000BF1E3A E8 E1 3F EE FF                          call    sub_AD5E20
.text:0000000000BF1E3F
.text:0000000000BF1E3F                         loc_BF1E3F:                             ; CODE XREF: sub_BF1850+1B0↑j
.text:0000000000BF1E3F                                                                 ; sub_BF1850+1BD↑j ...
.text:0000000000BF1E3F 40 38 B7 6C 3D 00 00                    cmp     [rdi+3D6Ch], sil
.text:0000000000BF1E46 74 6E                                   jz      short loc_BF1EB6
.text:0000000000BF1E48 40 38 B7 A9 15 00 00                    cmp     [rdi+15A9h], sil
.text:0000000000BF1E4F 74 6E                                   jz      short loc_BF1EBF
.text:0000000000BF1E51 48 8B 07                                mov     rax, [rdi]
.text:0000000000BF1E54 48 8B CF                                mov     rcx, rdi
.text:0000000000BF1E57 FF 90 B0 04 00 00                       call    qword ptr [rax+4B0h]
.text:0000000000BF1E5D 84 C0                                   test    al, al
.text:0000000000BF1E5F 74 55                                   jz      short loc_BF1EB6
.text:0000000000BF1E61 0F B6 87 F3 03 00 00                    movzx   eax, byte ptr [rdi+3F3h]
.text:0000000000BF1E68 2C 02                                   sub     al, 2
.text:0000000000BF1E6A 41 3A C4                                cmp     al, r12b
.text:0000000000BF1E6D 77 47                                   ja      short loc_BF1EB6
.text:0000000000BF1E6F BA FF FF FF FF                          mov     edx, 0FFFFFFFFh
.text:0000000000BF1E74 48 8D 0D 5D D1 71 01                    lea     rcx, unk_230EFD8
.text:0000000000BF1E7B E8 F0 A1 C1 00                          call    sub_180C070
.text:0000000000BF1E80 48 85 C0                                test    rax, rax
.text:0000000000BF1E83 75 0B                                   jnz     short loc_BF1E90
.text:0000000000BF1E85 48 8B 05 54 D1 71 01                    mov     rax, cs:qword_230EFE0
.text:0000000000BF1E8C 48 8B 40 08                             mov     rax, [rax+8]
.text:0000000000BF1E90
.text:0000000000BF1E90                         loc_BF1E90:                             ; CODE XREF: sub_BF1850+633↑j
.text:0000000000BF1E90 48 8D 15 49 4E EE 00                    lea     rdx, aBuyrandom ; "buyrandom"
.text:0000000000BF1E97 48 8B 0D 3A 2D 71 01                    mov     rcx, cs:qword_2304BD8
.text:0000000000BF1E9E 40 38 30                                cmp     [rax], sil
.text:0000000000BF1EA1 75 07                                   jnz     short loc_BF1EAA
.text:0000000000BF1EA3 48 8D 15 E2 95 ED 00                    lea     rdx, aRebuy     ; "rebuy"
.text:0000000000BF1EAA
.text:0000000000BF1EAA                         loc_BF1EAA:                             ; CODE XREF: sub_BF1850+651↑j
.text:0000000000BF1EAA E8 B1 1A F5 FF                          call    sub_B43960
.text:0000000000BF1EAF 40 88 B7 6C 3D 00 00                    mov     [rdi+3D6Ch], sil
.text:0000000000BF1EB6
.text:0000000000BF1EB6                         loc_BF1EB6:                             ; CODE XREF: sub_BF1850+5F6↑j
.text:0000000000BF1EB6                                                                 ; sub_BF1850+60F↑j ...
.text:0000000000BF1EB6 40 38 B7 A9 15 00 00                    cmp     [rdi+15A9h], sil
.text:0000000000BF1EBD 75 08                                   jnz     short loc_BF1EC7
.text:0000000000BF1EBF
.text:0000000000BF1EBF                         loc_BF1EBF:                             ; CODE XREF: sub_BF1850+5FF↑j
.text:0000000000BF1EBF 48 8B CF                                mov     rcx, rdi
.text:0000000000BF1EC2 E8 89 E9 02 00                          call    CallsGetSpread_sub_C20850 <= We hook inside this function



.text:0000000000C20850                         CallsGetSpread_sub_C20850 proc near     ; CODE XREF: sub_BF1850+672↑p
.text:0000000000C20850                                                                 ; sub_C14BA0+139↑p
.text:0000000000C20850                                                                 ; DATA XREF: ...
.text:0000000000C20850
.text:0000000000C20850                         var_38          = xmmword ptr -38h
.text:0000000000C20850                         var_28          = xmmword ptr -28h
.text:0000000000C20850                         var_18          = xmmword ptr -18h
.text:0000000000C20850                         arg_0           = qword ptr  8
.text:0000000000C20850                         arg_8           = qword ptr  10h
.text:0000000000C20850
.text:0000000000C20850 48 89 5C 24 10                          mov     [rsp+arg_8], rbx
.text:0000000000C20855 57                                      push    rdi
.text:0000000000C20856 48 83 EC 50                             sub     rsp, 50h
.text:0000000000C2085A 48 8B D9                                mov     rbx, rcx
.text:0000000000C2085D E8 8E 35 C2 FF                          call    sub_843DF0
.text:0000000000C20862 48 8B F8                                mov     rdi, rax
.text:0000000000C20865 48 85 C0                                test    rax, rax
.text:0000000000C20868 0F 84 C0 00 00 00                       jz      loc_C2092E
.text:0000000000C2086E
.text:0000000000C2086E                         loc_C2086E:                             ; DATA XREF: .rdata:0000000001E75878↓o
.text:0000000000C2086E                                                                 ; .rdata:0000000001E75894↓o ...
.text:0000000000C2086E 48 89 74 24 60                          mov     [rsp+58h+arg_0], rsi
.text:0000000000C20873 48 8B B3 10 14 00 00                    mov     rsi, [rbx+1410h]
.text:0000000000C2087A 48 85 F6                                test    rsi, rsi
.text:0000000000C2087D 0F 84 A6 00 00 00                       jz      loc_C20929
.text:0000000000C20883 48 8B 08                                mov     rcx, [rax]
.text:0000000000C20886 45 33 C0                                xor     r8d, r8d
.text:0000000000C20889
.text:0000000000C20889                         loc_C20889:                             ; DATA XREF: .rdata:0000000001E75894↓o
.text:0000000000C20889                                                                 ; .rdata:0000000001E758A4↓o ...
.text:0000000000C20889 0F 29 74 24 40                          movaps  [rsp+58h+var_18], xmm6
.text:0000000000C2088E 33 D2                                   xor     edx, edx
.text:0000000000C20890 0F 29 7C 24 30                          movaps  [rsp+58h+var_28], xmm7
.text:0000000000C20895 44 0F 29 44 24 20                       movaps  [rsp+58h+var_38], xmm8
.text:0000000000C2089B 4C 8B 89 D0 0C 00 00                    mov     r9, [rcx+0CD0h]
.text:0000000000C208A2 48 8B C8                                mov     rcx, rax
.text:0000000000C208A5 41 FF D1                                call    r9
.text:0000000000C208A8 48 8B 07                                mov     rax, [rdi]
.text:0000000000C208AB 48 8B CF                                mov     rcx, rdi
.text:0000000000C208AE 44 0F 28 C0                             movaps  xmm8, xmm0
.text:0000000000C208B2 FF 90 A8 0B 00 00                       call    qword ptr [rax+0BA8h]
.text:0000000000C208B8 48 8B 07                                mov     rax, [rdi]
.text:0000000000C208BB 48 8B CF                                mov     rcx, rdi
.text:0000000000C208BE F3 44 0F 58 C0                          addss   xmm8, xmm0
.text:0000000000C208C3 FF 90 18 0C 00 00                       call    qword ptr [rax+0C18h]
.text:0000000000C208C9 83 F8 02                                cmp     eax, 2
.text:0000000000C208CC 75 0A                                   jnz     short loc_C208D8
.text:0000000000C208CE F3 0F 10 3D AA CC DD 00                 movss   xmm7, cs:dword_19FD580
.text:0000000000C208D6 EB 08                                   jmp     short loc_C208E0
.text:0000000000C208D8                         ; ---------------------------------------------------------------------------
.text:0000000000C208D8
.text:0000000000C208D8                         loc_C208D8:                             ; CODE XREF: CallsGetSpread_sub_C20850+7C↑j
.text:0000000000C208D8 F3 0F 10 3D 08 94 CF 00                 movss   xmm7, cs:dword_1919CE8
.text:0000000000C208E0
.text:0000000000C208E0                         loc_C208E0:                             ; CODE XREF: CallsGetSpread_sub_C20850+86↑j
.text:0000000000C208E0 48 8B 1F                                mov     rbx, [rdi]
.text:0000000000C208E3 45 33 C0                                xor     r8d, r8d
.text:0000000000C208E6 33 D2                                   xor     edx, edx
.text:0000000000C208E8 48 8B CF                                mov     rcx, rdi
.text:0000000000C208EB FF 93 D0 0C 00 00                       call    qword ptr [rbx+0CD0h] ; Calls Get Spread ( We hook this )

*/
#define GET_SPREAD_CALLSITE_PATTERN "FF 93 ?? ?? ?? ?? BA 01 00 00 00 48 8B CF 0F 28 F0"



// @ client.dll xref "ang %.4f %.4f %.4f, pos %.4f %.4f %.4f\n"
/*
.text:0000000000794469 4C 8D 05 78 7A 2A 01                    lea     r8, aAng4f4f4fPos4f ; "ang %.4f %.4f %.4f, pos %.4f %.4f %.4f"...
.text:0000000000794470 F3 0F 10 4D A8                          movss   xmm1, [rbp+0E0h+var_138]
.text:0000000000794475 41 8B D7                                mov     edx, r15d
.text:0000000000794478 F3 0F 10 55 A4                          movss   xmm2, [rbp+0E0h+var_13C]
.text:000000000079447D F3 0F 10 65 B8                          movss   xmm4, dword ptr [rbp+0E0h+var_130+8]
.text:0000000000794482 F3 0F 10 5D B0                          movss   xmm3, dword ptr [rbp+0E0h+var_130]
.text:0000000000794487 F3 0F 10 6D B4                          movss   xmm5, dword ptr [rbp+0E0h+var_130+4]
.text:000000000079448C 8B 0D 42 4F B0 01                       mov     ecx, cs:dword_22993D4
.text:0000000000794492 0F 5A C0                                cvtps2pd xmm0, xmm0
.text:0000000000794495 0F 5A C9                                cvtps2pd xmm1, xmm1
.text:0000000000794498 F2 0F 11 44 24 40                       movsd   [rsp+200h+var_1C0], xmm0
.text:000000000079449E F2 0F 11 4C 24 38                       movsd   [rsp+200h+var_1C8], xmm1
.text:00000000007944A4 0F 5A D2                                cvtps2pd xmm2, xmm2
.text:00000000007944A7 0F 5A E4                                cvtps2pd xmm4, xmm4
.text:00000000007944AA F2 0F 11 54 24 30                       movsd   [rsp+200h+var_1D0], xmm2
.text:00000000007944B0 0F 5A DB                                cvtps2pd xmm3, xmm3
.text:00000000007944B3 0F 5A ED                                cvtps2pd xmm5, xmm5
.text:00000000007944B6 F2 0F 11 64 24 28                       movsd   [rsp+200h+var_1D8], xmm4
.text:00000000007944BC 66 49 0F 7E D9                          movq    r9, xmm3
.text:00000000007944C1 F2 0F 11 6C 24 20                       movsd   [rsp+200h+var_1E0], xmm5
.text:00000000007944C7 FF 15 EB 02 17 01                       call    cs:LoggingSystem_Log
.text:00000000007944CD
.text:00000000007944CD                         loc_7944CD:                             ; CODE XREF: sub_7940F0+372↑j
.text:00000000007944CD 83 FB FF                                cmp     ebx, 0FFFFFFFFh
.text:00000000007944D0 74 0E                                   jz      short loc_7944E0
.text:00000000007944D2 85 FF                                   test    edi, edi
.text:00000000007944D4 78 0A                                   js      short loc_7944E0
.text:00000000007944D6 8B D7                                   mov     edx, edi
.text:00000000007944D8 8B CB                                   mov     ecx, ebx
.text:00000000007944DA FF 15 28 F5 16 01                       call    cs:LoggingSystem_SetChannelIndent
.text:00000000007944E0
.text:00000000007944E0                         loc_7944E0:                             ; CODE XREF: sub_7940F0+229↑j
.text:00000000007944E0                                                                 ; sub_7940F0+23B↑j ...
.text:00000000007944E0 80 7D C8 00                             cmp     [rbp+0E0h+var_118], 0
.text:00000000007944E4 75 10                                   jnz     short loc_7944F6
.text:00000000007944E6 48 8B 06                                mov     rax, [rsi]
.text:00000000007944E9 48 8B CE                                mov     rcx, rsi
.text:00000000007944EC FF 90 08 0B 00 00                       call    qword ptr [rax+0B08h]
.text:00000000007944F2 84 C0                                   test    al, al
.text:00000000007944F4 75 12                                   jnz     short loc_794508
.text:00000000007944F6
.text:00000000007944F6                         loc_7944F6:                             ; CODE XREF: sub_7940F0+3F4↑j
.text:00000000007944F6 48 8B 0D 8B 93 D8 01                    mov     rcx, cs:qword_251D888
.text:00000000007944FD 33 D2                                   xor     edx, edx
.text:00000000007944FF 48 8B 01                                mov     rax, [rcx]
.text:0000000000794502 FF 90 E0 00 00 00                       call    qword ptr [rax+0E0h]
.text:0000000000794508
.text:0000000000794508                         loc_794508:                             ; CODE XREF: sub_7940F0+404↑j
.text:0000000000794508 48 8D 4D E0                             lea     rcx, [rbp+0E0h+var_108+8]
.text:000000000079450C E8 8F 72 9C FF                          call    unknown_libname_3 ; Microsoft VisualC v7/14 64bit runtime
.text:0000000000794511 0F 28 45 90                             movaps  xmm0, [rbp+0E0h+var_150]
.text:0000000000794515 4C 8D 45 24                             lea     r8, [rbp+0E0h+var_C8+0Ch]
.text:0000000000794519 0F 28 4D A0                             movaps  xmm1, xmmword ptr [rbp-60h]
.text:000000000079451D 48 8D 55 20                             lea     rdx, [rbp+0E0h+var_C8+8]
.text:0000000000794521 48 8B 06                                mov     rax, [rsi]
.text:0000000000794524 48 8B CE                                mov     rcx, rsi
.text:0000000000794527 0F 11 45 D8                             movups  xmmword ptr [rbp-28h], xmm0
.text:000000000079452B C6 45 2C 01                             mov     byte ptr [rbp+0E0h+var_B4], 1
.text:000000000079452F 0F 28 45 B0                             movaps  xmm0, [rbp+0E0h+var_130]
.text:0000000000794533 0F 11 4D E8                             movups  [rbp+0E0h+var_F8], xmm1
.text:0000000000794537 0F 28 4D C0                             movaps  xmm1, xmmword ptr [rbp-40h]
.text:000000000079453B 0F 11 45 F8                             movups  [rbp+0E0h+var_E8], xmm0
.text:000000000079453F 0F 11 4D 08                             movups  [rbp+0E0h+var_D8], xmm1
.text:0000000000794543 FF 90 E8 0C 00 00                       call    qword ptr [rax+0CE8h]
.text:0000000000794549 48 8B 56 10                             mov     rdx, [rsi+10h]
.text:000000000079454D 8B 4D D8                                mov     ecx, dword ptr [rbp+0E0h+var_108]
.text:0000000000794550 F3 0F 11 45 1C                          movss   dword ptr [rbp+0E0h+var_C8+4], xmm0
.text:0000000000794555 8B 52 38                                mov     edx, [rdx+38h]
.text:0000000000794558 E8 23 DC F6 FF                          call    sub_702180
.text:000000000079455D 0F 10 45 D8                             movups  xmm0, [rbp+0E0h+var_108]
.text:0000000000794561 89 45 18                                mov     dword ptr [rbp+0E0h+var_C8], eax
.text:0000000000794564 45 8B CD                                mov     r9d, r13d
.text:0000000000794567 0F 10 4D E8                             movups  xmm1, [rbp+0E0h+var_F8]
.text:000000000079456B 48 8D 55 90                             lea     rdx, [rbp+0E0h+var_150]
.text:000000000079456F 48 8B 06                                mov     rax, [rsi]
.text:0000000000794572 F3 0F 10 96 D0 19 00 00                 movss   xmm2, dword ptr [rsi+19D0h]
.text:000000000079457A 45 8B C4                                mov     r8d, r12d
.text:000000000079457D 0F 29 4D 40                             movaps  [rbp+0E0h+var_A0], xmm1
.text:0000000000794581 48 8B CE                                mov     rcx, rsi
.text:0000000000794584 0F 10 4D 08                             movups  xmm1, [rbp+0E0h+var_D8]
.text:0000000000794588 0F 29 45 30                             movaps  [rbp+0E0h+var_B0], xmm0
.text:000000000079458C 0F 10 45 F8                             movups  xmm0, [rbp+0E0h+var_E8]
.text:0000000000794590 0F 29 4D 60                             movaps  [rbp+0E0h+var_80], xmm1
.text:0000000000794594 F2 0F 10 4D 28                          movsd   xmm1, qword ptr [rbp+28h]
.text:0000000000794599 0F 29 45 50                             movaps  [rbp+0E0h+var_90], xmm0
.text:000000000079459D F3 0F 10 CA                             movss   xmm1, xmm2
.text:00000000007945A1 0F 10 45 18                             movups  xmm0, [rbp+0E0h+var_C8]
.text:00000000007945A5 F2 0F 11 8D 80 00 00 00                 movsd   [rbp+0E0h+var_60], xmm1
.text:00000000007945AD 0F 29 45 70                             movaps  [rbp+0E0h+var_70], xmm0
.text:00000000007945B1 FF 90 28 0D 00 00                       call    qword ptr [rax+0D28h]
.text:00000000007945B7 85 C0                                   test    eax, eax
.text:00000000007945B9 0F 85 3F 01 00 00                       jnz     loc_7946FE
.text:00000000007945BF 48 8B 06                                mov     rax, [rsi]
.text:00000000007945C2 33 D2                                   xor     edx, edx
.text:00000000007945C4 48 8B CE                                mov     rcx, rsi
.text:00000000007945C7
.text:00000000007945C7                         loc_7945C7:                             ; DATA XREF: .rdata:0000000001E1D3D8↓o
.text:00000000007945C7                                                                 ; .rdata:0000000001E1D3E8↓o ...
.text:00000000007945C7 44 0F 29 84 24 B0 01 00                 movaps  [rsp+200h+var_50], xmm8
.text:00000000007945C7 00
.text:00000000007945D0 FF 90 48 0A 00 00                       call    qword ptr [rax+0A48h]
.text:00000000007945D6 49 8B CE                                mov     rcx, r14
.text:00000000007945D9 44 8B E8                                mov     r13d, eax
.text:00000000007945DC E8 4F 4E A6 FF                          call    sub_1F9430
.text:00000000007945E1 48 8B 8E 90 03 00 00                    mov     rcx, [rsi+390h]
.text:00000000007945E8 F3 44 0F 10 86 D0 19 00                 movss   xmm8, dword ptr [rsi+19D0h]
.text:00000000007945E8 00
.text:00000000007945F1 48 89 45 D0                             mov     [rbp+0E0h+var_110], rax
.text:00000000007945F5 83 B9 48 06 00 00 01                    cmp     dword ptr [rcx+648h], 1
.text:00000000007945FC 75 16                                   jnz     short loc_794614
.text:00000000007945FE 48 8B 16                                mov     rdx, [rsi]
.text:0000000000794601 48 8B CE                                mov     rcx, rsi
.text:0000000000794604 FF 92 10 0D 00 00                       call    qword ptr [rdx+0D10h]
.text:000000000079460A 84 C0                                   test    al, al
.text:000000000079460C 74 06                                   jz      short loc_794614
.text:000000000079460E 41 BF 09 00 00 00                       mov     r15d, 9
.text:0000000000794614
.text:0000000000794614                         loc_794614:                             ; CODE XREF: sub_7940F0+50C↑j
.text:0000000000794614                                                                 ; sub_7940F0+51C↑j
.text:0000000000794614 48 8B 06                                mov     rax, [rsi]
.text:0000000000794617 48 8B CE                                mov     rcx, rsi
.text:000000000079461A FF 90 C0 0B 00 00                       call    qword ptr [rax+0BC0h]
.text:0000000000794620 48 8B 06                                mov     rax, [rsi]
.text:0000000000794623 45 33 C0                                xor     r8d, r8d
.text:0000000000794626 33 D2                                   xor     edx, edx
.text:0000000000794628 48 8B CE                                mov     rcx, rsi
.text:000000000079462B 0F 28 F8                                movaps  xmm7, xmm0
.text:000000000079462E FF 90 E8 0C 00 00                       call    qword ptr [rax+0CE8h]
.text:0000000000794634 44 8B 45 90                             mov     r8d, dword ptr [rbp+0E0h+var_150]
.text:0000000000794638 48 8D 55 B0                             lea     rdx, [rbp+0E0h+var_130]
.text:000000000079463C 49 8B CE                                mov     rcx, r14
.text:000000000079463F 0F 28 F0                                movaps  xmm6, xmm0
.text:0000000000794642 E8 D9 F0 4F 00                          call    ComputeRandomSeed_sub_C93720 ; We need this function
.text:0000000000794647 48 8B CE                                mov     rcx, rsi
.text:000000000079464A 8B D8                                   mov     ebx, eax

*/
#define COMPUTE_RANDOM_SEED_PATTERN "48 89 5C 24 08 57 48 81 EC F0"




// @ client -> xref "progress_this_match"
/*

.text:0000000000FAE2F4 E8 A7 8A 93 FF                          call    GetControllerByIdx_sub_8E6DA0
.text:0000000000FAE2F9 48 8B D8                                mov     rbx, rax
.text:0000000000FAE2FC 48 85 C0                                test    rax, rax
.text:0000000000FAE2FF 0F 84 CF 01 00 00                       jz      loc_FAE4D4
.text:0000000000FAE305 48 8B C8                                mov     rcx, rax
.text:0000000000FAE308
.text:0000000000FAE308                         loc_FAE308:                             ; DATA XREF: .rdata:0000000001EC31EC↓o
.text:0000000000FAE308                                                                 ; .rdata:0000000001EC3208↓o ...
.text:0000000000FAE308 4C 89 7C 24 70                          mov     [rsp+98h+var_28], r15
.text:0000000000FAE30D E8 AE 8B 85 FF                          call    sub_806EC0
.text:0000000000FAE312 48 83 7D 28 00                          cmp     qword ptr [rbp+28h], 0
.text:0000000000FAE317 44 8B F8                                mov     r15d, eax
.text:0000000000FAE31A 0F 84 AF 01 00 00                       jz      loc_FAE4CF
.text:0000000000FAE320 85 C0                                   test    eax, eax
.text:0000000000FAE322 0F 84 A7 01 00 00                       jz      loc_FAE4CF
.text:0000000000FAE328 48 8B CB                                mov     rcx, rbx
.text:0000000000FAE32B E8 A0 8B 85 FF                          call    sub_806ED0
.text:0000000000FAE330 85 C0                                   test    eax, eax
.text:0000000000FAE332 0F 84 97 01 00 00                       jz      loc_FAE4CF
.text:0000000000FAE338
.text:0000000000FAE338                         loc_FAE338:                             ; DATA XREF: .rdata:0000000001EC3208↓o
.text:0000000000FAE338                                                                 ; .rdata:0000000001EC3218↓o ...
.text:0000000000FAE338 48 89 B4 24 A0 00 00 00                 mov     [rsp+98h+arg_0], rsi
.text:0000000000FAE340 33 F6                                   xor     esi, esi
.text:0000000000FAE342 48 89 BC 24 A8 00 00 00                 mov     [rsp+98h+arg_8], rdi
.text:0000000000FAE34A 8B FE                                   mov     edi, esi
.text:0000000000FAE34C 4C 89 6C 24 78                          mov     [rsp+98h+var_20], r13
.text:0000000000FAE351 E8 4A 1C 81 FF                          call    sub_7BFFA0
.text:0000000000FAE356 48 8B 88 40 F5 03 00                    mov     rcx, [rax+3F540h]
.text:0000000000FAE35D 48 85 C9                                test    rcx, rcx
.text:0000000000FAE360 74 29                                   jz      short loc_FAE38B
.text:0000000000FAE362 BA 10 00 00 00                          mov     edx, 10h
.text:0000000000FAE367 E8 E4 3C 81 FF                          call    sub_7C2050
.text:0000000000FAE36C 48 85 C0                                test    rax, rax
.text:0000000000FAE36F 74 1A                                   jz      short loc_FAE38B
.text:0000000000FAE371 39 70 08                                cmp     [rax+8], esi
.text:0000000000FAE374 76 15                                   jbe     short loc_FAE38B
.text:0000000000FAE376 48 8B 40 10                             mov     rax, [rax+10h]
.text:0000000000FAE37A 48 8B 08                                mov     rcx, [rax]
.text:0000000000FAE37D 48 85 C9                                test    rcx, rcx
.text:0000000000FAE380 74 09                                   jz      short loc_FAE38B
.text:0000000000FAE382 44 39 79 28                             cmp     [rcx+28h], r15d
.text:0000000000FAE386 75 03                                   jnz     short loc_FAE38B
.text:0000000000FAE388 8B 79 2C                                mov     edi, [rcx+2Ch]
.text:0000000000FAE38B
.text:0000000000FAE38B                         loc_FAE38B:                             ; CODE XREF: sub_FAE2E0+80↑j
.text:0000000000FAE38B                                                                 ; sub_FAE2E0+8F↑j ...
.text:0000000000FAE38B 48 63 8D 90 00 00 00                    movsxd  rcx, dword ptr [rbp+90h]
.text:0000000000FAE392 48 8B 85 98 00 00 00                    mov     rax, [rbp+98h]
.text:0000000000FAE399 3B 7C 88 FC                             cmp     edi, [rax+rcx*4-4]
.text:0000000000FAE39D 0F 83 17 01 00 00                       jnb     loc_FAE4BA
.text:0000000000FAE3A3 48 8B 4D 28                             mov     rcx, [rbp+28h]
.text:0000000000FAE3A7 FF 15 53 63 95 00                       call    cs:?GetName@KeyValues@@QEBAPEBDXZ ; KeyValues::GetName(void)
.text:0000000000FAE3AD 48 8B C8                                mov     rcx, rax
.text:0000000000FAE3B0 FF 15 6A 64 95 00                       call    cs:V_atoi
.text:0000000000FAE3B6 48 8D 0D D3 A8 0C 01                    lea     rcx, unk_2078C90
.text:0000000000FAE3BD 89 84 24 B0 00 00 00                    mov     [rsp+98h+arg_10], eax
.text:0000000000FAE3C4 48 89 4C 24 40                          mov     [rsp+98h+var_58], rcx
.text:0000000000FAE3C9 48 8D 84 24 B0 00 00 00                 lea     rax, [rsp+98h+arg_10]
.text:0000000000FAE3D1 48 89 4C 24 50                          mov     [rsp+98h+var_48], rcx
.text:0000000000FAE3D6 4C 8D 44 24 40                          lea     r8, [rsp+98h+var_58]
.text:0000000000FAE3DB 48 8D 0D B6 A8 0C 01                    lea     rcx, dword_2078C98
.text:0000000000FAE3E2 48 89 44 24 48                          mov     [rsp+98h+var_50], rax
.text:0000000000FAE3E7 48 8D 54 24 30                          lea     rdx, [rsp+98h+var_68]
.text:0000000000FAE3EC E8 2F B1 C9 FF                          call    sub_C49520
.text:0000000000FAE3F1 8B 48 04                                mov     ecx, [rax+4]
.text:0000000000FAE3F4 83 F9 FF                                cmp     ecx, 0FFFFFFFFh
.text:0000000000FAE3F7 74 33                                   jz      short loc_FAE42C
.text:0000000000FAE3F9 F7 05 99 A8 0C 01 FF FF                 test    dword ptr cs:qword_2078C9C, 7FFFFFFFh
.text:0000000000FAE3F9 FF 7F
.text:0000000000FAE403 48 8B 15 96 A8 0C 01                    mov     rdx, cs:qword_2078C9C+4
.text:0000000000FAE40A 48 0F 44 D6                             cmovz   rdx, rsi
.text:0000000000FAE40E 48 6B C9 38                             imul    rcx, 38h ; '8'
.text:0000000000FAE412 48 8D 04 11                             lea     rax, [rcx+rdx]
.text:0000000000FAE416 40 38 74 11 2D                          cmp     [rcx+rdx+2Dh], sil
.text:0000000000FAE41B 75 08                                   jnz     short loc_FAE425
.text:0000000000FAE41D 89 78 30                                mov     [rax+30h], edi
.text:0000000000FAE420 C6 44 11 2D 01                          mov     byte ptr [rcx+rdx+2Dh], 1
.text:0000000000FAE425
.text:0000000000FAE425                         loc_FAE425:                             ; CODE XREF: sub_FAE2E0+13B↑j
.text:0000000000FAE425 8B 78 30                                mov     edi, [rax+30h]
.text:0000000000FAE428 8B 74 11 18                             mov     esi, [rcx+rdx+18h]
.text:0000000000FAE42C
.text:0000000000FAE42C                         loc_FAE42C:                             ; CODE XREF: sub_FAE2E0+117↑j
.text:0000000000FAE42C 49 8B 1E                                mov     rbx, [r14]
.text:0000000000FAE42F 48 8B 5B 08                             mov     rbx, [rbx+8]
.text:0000000000FAE433 48 8B CB                                mov     rcx, rbx        ; this
.text:0000000000FAE436 E8 30 D2 88 00                          call    ?Enter@Isolate@v8@@QEAAXXZ ; v8::Isolate::Enter(void)
.text:0000000000FAE43B 49 8B 16                                mov     rdx, [r14]
.text:0000000000FAE43E 48 8D 4C 24 58                          lea     rcx, [rsp+98h+var_40] ; this
.text:0000000000FAE443 48 8B 52 08                             mov     rdx, [rdx+8]    ; struct v8::Isolate *
.text:0000000000FAE447 E8 AD D1 88 00                          call    ??0HandleScope@v8@@QEAA@PEAVIsolate@1@@Z ; v8::HandleScope::HandleScope(v8::Isolate *)
.text:0000000000FAE44C 49 8B 16                                mov     rdx, [r14]
.text:0000000000FAE44F 4C 8D 45 30                             lea     r8, [rbp+30h]
.text:0000000000FAE453 45 8B CF                                mov     r9d, r15d
.text:0000000000FAE456 89 7C 24 20                             mov     [rsp+98h+var_78], edi
.text:0000000000FAE45A 48 8D 8C 24 B8 00 00 00                 lea     rcx, [rsp+98h+arg_18]
.text:0000000000FAE462 48 8B 52 08                             mov     rdx, [rdx+8]
.text:0000000000FAE466 E8 95 4D 78 FF                          call    sub_733200
.text:0000000000FAE46B 44 8B C6                                mov     r8d, esi
.text:0000000000FAE46E 48 8D 15 03 B5 B9 00                    lea     rdx, aProgressThisMa ; "progress_this_match"


ControllerByIdx_sub_8E6DA0 = GetControllerByIdx_sub_8E6DA0(0);
  v5 = ControllerByIdx_sub_8E6DA0;
  if ( ControllerByIdx_sub_8E6DA0 )
  {
    v6 = sub_806EC0(ControllerByIdx_sub_8E6DA0);
    v7 = v6;
    if ( *(_QWORD *)(a1 + 40) )
    {
      if ( v6 && (unsigned int)sub_806ED0(v5) )
      {
        v8 = 0;
        v9 = 0;
        v10 = *(_QWORD *)(sub_7BFFA0() + 259392);
        if ( v10 )
        {
          v11 = sub_7C2050(v10, 16);
          if ( v11 )
          {
            if ( *(_DWORD *)(v11 + 8) )
            {
              v12 = **(_QWORD **)(v11 + 16);
              if ( v12 )
              {
                if ( *(_DWORD *)(v12 + 40) == v7 )
                  v9 = *(_DWORD *)(v12 + 44);
              }
            }
          }
        }
        if ( v9 < *(_DWORD *)(*(_QWORD *)(a1 + 152) + 4LL * *(int *)(a1 + 144) - 4) )
        {
          Name = KeyValues::GetName(*(KeyValues **)(a1 + 40));
          v24 = V_atoi(Name);
          v22[0] = &unk_2078C90;
          v22[2] = &unk_2078C90;
          v22[1] = &v24;
          v14 = *(unsigned int *)(sub_C49520(&dword_2078C98, v21, v22) + 4);
          if ( (_DWORD)v14 != -1 )
          {
            v15 = *(__int64 *)((char *)&qword_2078C9C + 4);
            if ( (qword_2078C9C & 0x7FFFFFFF) == 0 )
              v15 = 0;
            v16 = 56 * v14;
            v17 = v16 + v15;
            if ( !*(_BYTE *)(v16 + v15 + 45) )
            {
              *(_DWORD *)(v17 + 48) = v9;
              *(_BYTE *)(v16 + v15 + 45) = 1;
            }
            v9 = *(_DWORD *)(v17 + 48);
            v8 = *(_DWORD *)(v16 + v15 + 24);
          }
          v18 = *(v8::Isolate **)(*a2 + 8);
          v8::Isolate::Enter(v18);
          v8::HandleScope::HandleScope((v8::HandleScope *)v23, *(struct v8::Isolate **)(*a2 + 8));
          sub_733200((unsigned int)&v25, *(_QWORD *)(*a2 + 8), a1 + 48, v7, v9);
          sub_731FD0(&v25, "progress_this_match", v8);
*/
#define GET_CONTROLLER_BY_INDEX "E8 ?? ?? ?? ?? 48 3B D8 75 2B"




// @ client -> xref "CPointClientUIDialog::OnDialogActivatorChanged"

/*

00000000018ED12 44 0F B6 C0                             movzx   r8d, al
.text:000000000018ED16 48 8D 15 6B 01 79 01                    lea     rdx, aCpointclientui_3 ; "CPointClientUIDialog::OnDialogActivator"...
.text:000000000018ED1D 48 8D 4C 24 20                          lea     rcx, [rsp+48h+var_28]
.text:000000000018ED22 E8 79 62 94 00                          call    sub_AD4FA0
.text:000000000018ED27 33 C9                                   xor     ecx, ecx        ; a1
.text:000000000018ED29 E8 B2 80 75 00                          call    GetPawnByIdx_sub_8E6DE0
.text:000000000018ED2E 4C 8B 1D AB F1 17 02                    mov     r11, cs:qword_230DEE0
.text:000000000018ED35 48 8B D8                                mov     rbx, rax
.text:000000000018ED38 44 8B 87 B8 0E 00 00                    m

*/
#define GET_PAWN_BY_INDEX "48 83 EC 28 83 F9 FF 75 17 48 8B 0D ?? ?? ?? ?? 48 8D 54 24 30 48 8B 01 FF 90 ?? ?? ?? ?? 8B 08 48 63 C1 4C"