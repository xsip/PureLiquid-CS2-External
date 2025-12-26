#pragma once
#include <GlobalData/Include.h>
#include <Source2/CBaseHandle.h>
namespace CS2 {
	namespace client {
		class C_BasePlayerPawn;
		class CCSPlayerController {
		public:
			PROPERTY(m_hPawn, Source2::CBaseHandle<client::C_BasePlayerPawn>, 0x6b4);
		};
	}
}