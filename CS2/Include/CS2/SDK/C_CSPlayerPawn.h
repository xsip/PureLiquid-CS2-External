#pragma once
#include <GlobalData/Include.h>
#include <Math/Vector.h>
namespace CS2 {
	namespace client {
		class C_CSPlayerPawn {
		public:
			PROPERTY(m_vecViewOffset, Vector, 0xd80);
			PROPERTY(m_vOldOrigin, Vector, 0x15a0);
			PROPERTY(m_iMaxHealth, int32_t, 0x348);
			PROPERTY(m_iHealth, int32_t, 0x34c);
		};
	}
}