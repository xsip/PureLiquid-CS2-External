#pragma once
#include <GlobalData/Include.h>
#include <Math/QAngle.h>
namespace CS2 {

	enum ECommandButtons : uint64_t {
		IN_ATTACK = (1 << 0),
		IN_JUMP = (1 << 1),
		IN_DUCK = (1 << 2),
		IN_FORWARD = (1 << 3),
		IN_BACK = (1 << 4),
		IN_USE = (1 << 5),
		IN_CANCEL = (1 << 6),
		IN_LEFT = (1 << 7),
		IN_RIGHT = (1 << 8),
		IN_MOVELEFT = (1 << 9),
		IN_MOVERIGHT = (1 << 10),
		IN_ATTACK2 = (1 << 11),
		IN_RUN = (1 << 12),
		IN_RELOAD = (1 << 13),
		IN_ALT1 = (1 << 14),
		IN_ALT2 = (1 << 15),
		IN_SCORE = (1 << 16),
		IN_SPEED = (1 << 17),
		IN_WALK = (1 << 18),
		IN_ZOOM = (1 << 19),
		IN_WEAPON1 = (1 << 20),
		IN_WEAPON2 = (1 << 21),
		IN_BULLRUSH = (1 << 22),
		IN_GRENADE1 = (1 << 23),
		IN_GRENADE2 = (1 << 24),
		IN_LOOKSPIN = (1 << 25),
	};

	enum EInputHistoryBits : std::uint32_t
	{
		INPUT_HISTORY_BITS_VIEWANGLES = 0x1U,
		INPUT_HISTORY_BITS_SHOOTPOSITION = 0x2U,
		INPUT_HISTORY_BITS_TARGETHEADPOSITIONCHECK = 0x4U,
		INPUT_HISTORY_BITS_TARGETABSPOSITIONCHECK = 0x8U,
		INPUT_HISTORY_BITS_TARGETANGCHECK = 0x10U,
		INPUT_HISTORY_BITS_CL_INTERP = 0x20U,
		INPUT_HISTORY_BITS_SV_INTERP0 = 0x40U,
		INPUT_HISTORY_BITS_SV_INTERP1 = 0x80U,
		INPUT_HISTORY_BITS_PLAYER_INTERP = 0x100U,
		INPUT_HISTORY_BITS_RENDERTICKCOUNT = 0x200U,
		INPUT_HISTORY_BITS_RENDERTICKFRACTION = 0x400U,
		INPUT_HISTORY_BITS_PLAYERTICKCOUNT = 0x800U,
		INPUT_HISTORY_BITS_PLAYERTICKFRACTION = 0x1000U,
		INPUT_HISTORY_BITS_FRAMENUMBER = 0x2000U,
		INPUT_HISTORY_BITS_TARGETENTINDEX = 0x4000U
	};

	// TODO: fix structures! it should extend CBasePb instead of  class CBasePB* base;!

	class CMsgQAngle
	{
	public:
		class CBasePB* base; //0x00
		char pad_0008[16]; //0x08
		QAngle angValue; //0x18
		char pad_0024[92]; //0x24
	}; //Size: 0x0080

	class CBasePB
	{
	public:
		char pad_0000[8]; //0x0000
		std::uint32_t has_bits; //0x0004
		std::uint64_t cached_bits; //0x0012

		void set_bits(std::uint64_t bits)
		{
			cached_bits |= bits;
		}
	}; //Size: 0x0012

	class CCSGOInterpolationInfoPB	{
	public:
		class CBasePB* base; //0x00
		char pad_0008[16]; //0x08
		float flFraction; //0x18
		int32_t nSrcTick; //0x1C
		int32_t nDstTick; //0x20
		char pad_0024[28]; //0x24
	}; //Size: 0x0040

	class CInButtonStatePB
	{
	public:
		class CBasePB* base; //0x00
		int64_t nValue; //0x08
		int64_t nValueChanged; //0x10
		int64_t nValueScroll; //0x18
		char pad_0020[32]; //0x20
	}; //Size: 0x0040

	class CSubtickMoveStep
	{
	public:
		class CBasePB* base; //0x00
		char pad_0008[16]; //0x08
		int64_t nButton; //0x18
		bool nPressed; //0x20
		char pad_0021[3]; //0x21
		float flWhen; //0x24
		float flAnalogForwardDelta; //0x28
		float flAnalogLeftDelta; //0x2C
		char pad_0030[24]; //0x30
	}; //Size: 0x0048

	class CSGOInputHistoryEntryPB: public CBasePB
	{
	public:
		class CMsgQAngle* pViewCmd; //0x18
		class CMsgQAngle* pShootPosition; //0x20
		char pad_0028[24]; //0x28
	}; //Size: 0x0040

	static_assert(offsetof(CSGOInputHistoryEntryPB, pViewCmd) == 0x18);
	
	class CBaseUserCmdPB
	{
	public:
		void* __vftable; //0x00
		uint32_t nHasBits; //0x08
		int64_t nCachedBits; //0x0C
		void* pArena; //0x14
		int32_t nCurrentSize; //0x1C
		int32_t nTotalSize; //0x20
		class CSubtickMoveStep* pRep; //0x24
		char pad_002C[8]; //0x2C
		class CInButtonStatePB* pInButtonState; //0x34
		class CMsgQAngle* pViewAngles; //0x3C
		int32_t nLegacyCommandNumber; //0x44
		int32_t nClientTick; //0x48
		float flForwardMove; //0x4C
		float flSideMove; //0x50
		float flUpMove; //0x54
		int32_t nImpulse; //0x58
		int32_t nWeaponSelect; //0x5C
		int32_t nRandomSeed; //0x60
		int32_t nMousedX; //0x64
		int32_t nMousedY; //0x68
		uint32_t nConsumedServerAngleChanges; //0x6C
		int32_t nCmdFlags; //0x70
		uint32_t nPawnEntityHandle; //0x74
		char pad_0078[4]; //0x78
	}; //Size: 0x007C

	class CCSGOUserCmdPB
	{
	public:
		uint32_t nHasBits; //0x00
		char pad_0004[4]; //0x04
		uint64_t nCachedSize; //0x08
		char pad_0010[24]; //0x10
		class CBaseUserCmdPB* pBaseCmd; //0x28
		char pad_0030[16]; //0x30
	}; //Size: 0x0040

	class CInButtonState
	{
	public:
		void* __vftable; //0x00
		int64_t nValue; //0x08
		int64_t nValueChanged; //0x10
		int64_t nValueScroll; //0x18
		char pad_0020[32]; //0x20
	}; //Size: 0x0040

	class CUserCmd
	{
	public:
		void* __vftable; //0x00
		char pad_0008[16]; //0x08
		class CCSGOUserCmdPB csgoUserCmd; //0x18
		class CInButtonState nButtons; //0x58
		char pad_0098[24]; //0x98
	}; //Size: 0x00B0
	static_assert(offsetof(CUserCmd, nButtons) == 0x58);



	struct CreateMoveHookData
	{
		uint64_t originalFunc;
		uint64_t cmd;       
		uint64_t btnToForce;
		Vector3 vViewAnglesToSet;
		bool bForceSubtickViewAngle;
		bool bForceBtn;
		bool bForcedBtn;
	};

    class CCSGOInput {
    private:
		// CreateMove Hook
		inline static bool m_bIsHooked = false;
		inline static void* m_pDataRemote = nullptr;
		inline static void* m_pShellcodeRemote = nullptr;
		inline static uintptr_t m_pTargetFunction = 0;


		// CreateMove Shellcode
		static double __fastcall CreateMove_Hook_Shellcode(
			int64_t a1, unsigned int a2, CUserCmd* cmd);
		static void CreateMove_Hook_Shellcode_End();

		static uintptr_t FindCreateMove();
		// ViewAngles Disp Resolver
        inline static uint32_t pViewAnglesOffset = 0x0;
        static uintptr_t ResolveViewAnglesOffset();

    public:
        RUNTIME_OFFSET_PROPERTY(vViewAngles, QAngle_t, ResolveViewAnglesOffset)

		bool HookCreateMove();
		bool UnhookCreateMove();

		CreateMoveHookData GetExecutionData();
		void ForceButton(ECommandButtons btn);
		void Attack();
		void SetSubTickAngle(Vector vAngle);
		bool IsHooked() { return m_bIsHooked; }
    };
}