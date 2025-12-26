#pragma once
#include <Windows.h>
#include <cstdint>
#include <cstddef>
#include <array>
#include <Math/Vector.h>

namespace CS2 {

	namespace client {
		class C_CSPlayerPawn;
	}

	class CGameTraceManager;

	enum RayType_t : uint8_t
	{
		RAY_TYPE_LINE = 0,
		RAY_TYPE_SPHERE,
		RAY_TYPE_HULL,
		RAY_TYPE_CAPSULE,
		RAY_TYPE_MESH,
	};

	struct Ray_t
	{
		Ray_t() { Init(Vector3(0.0f, 0.0f, 0.0f)); }
		void Init(const Vector3& vStartOffset)
		{
			m_Line.m_vStartOffset = vStartOffset;
			m_Line.m_flRadius = 0.0f;
			m_eType = RAY_TYPE_LINE;
		}
		struct Line_t
		{
			Vector m_vStartOffset;
			float m_flRadius;
		};

		struct Sphere_t
		{
			Vector m_vCenter;
			float m_flRadius;
		};

		struct Hull_t
		{
			Vector m_vMins;
			Vector m_vMaxs;
		};

		struct Capsule_t
		{
			Vector m_vCenter[2];
			float m_flRadius;
		};

		struct Mesh_t
		{
			Vector m_vMins;
			Vector m_vMaxs;
			const Vector* m_pVertices;
			int m_nNumVertices;
		};

		union
		{
			Line_t 		m_Line;
			Sphere_t 	m_Sphere;
			Hull_t 		m_Hull;
			Capsule_t 	m_Capsule;
			Mesh_t 		m_Mesh;
		};

		RayType_t m_eType;
	};

	struct trace_t {
		uint8_t pad1[8];
		void* HitEntity; //hit pawn
		void/*CHitBox**/* hitbox;
		uint8_t pad2[0x60];
		Vector3 Start;
		Vector3 End;
		uint8_t pad3[0x1C];
		float Fraction;
		uint8_t pad4[6];
		bool bHit;
		uint8_t pad5[0x20];
	};

	struct TraceFilter_t
	{
		std::byte pad01[0x8];					
		std::int64_t m_uTraceMask;						
		std::array<std::int64_t, 2> m_v1;				
		std::array<std::int32_t, 4> m_arrSkipHandles; 
		std::array<std::int16_t, 2> m_arrCollisions;   
		std::int16_t m_v2;							
		std::uint8_t m_nLayer;							
		std::uint8_t m_v4;								
		std::uint8_t m_flags;							

		TraceFilter_t() = default;
		static TraceFilter_t* InitEntitiesOnly(client::C_CSPlayerPawn* skip, uint32_t mask, int layer, bool bDebug = true);
	};
	using InitTraceFilterFn = TraceFilter_t * (__thiscall*)(void*, client::C_CSPlayerPawn*, uint32_t, int, int16_t);

	using TraceShapeFnDef = bool(__fastcall*)(void*, Ray_t*, const Vector&, const Vector&, TraceFilter_t*, trace_t*);

	struct TraceShapeCtx {
		TraceShapeFnDef TraceShape;
		CGameTraceManager* pGameTraceManager;
		TraceFilter_t* pTraceFilter;
		Vector vStartPos;
		Vector vEndPos;
		trace_t* pTrace;
		Ray_t* ray;
	};
	struct InitEntityTraceFilterCtx {
		TraceFilter_t* filter;
		InitTraceFilterFn fn;
		client::C_CSPlayerPawn* pSkipPawn;
		uint32_t mask;
		int layer;
	};



	class CGameTraceManager {
	private:
		inline static TraceFilter_t* pLastUsedTraceShapeFilter = nullptr;
		inline static client::C_CSPlayerPawn* pLastUsedPawn = nullptr;
		inline static TraceShapeCtx* pTraceShapeRemoteCtx = nullptr;
		inline static void* pTraceShapeShellcodeRemote = nullptr;
		inline static TraceShapeFnDef TraceShapeFn = nullptr;
		inline static trace_t* pLastUsedTrace = nullptr;
		inline static Ray_t* pLastUsedRay = nullptr;
	public:
		bool IsPlayerVisible(client::C_CSPlayerPawn* pLocal, client::C_CSPlayerPawn* pEnemy, bool bDebug = true);
	};
}
