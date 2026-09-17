#include <CS2/ExtendedSDK/client/CGameSceneNode.h>
#include <CS2/SDK/client/CGameSceneNode.hpp>
#include <GlobalData/Include.h>
#include <CS2/Patterns.h>
using namespace Globals;
namespace CS2 {
	namespace client {

		uint32_t client::CGameSceneNodeExtended::GetBonesOffset()
		{
			if (!dwBonesOffset) {
				auto hClient = pProc->GetRemoteModule("client.dll");
				if (!hClient || hClient && !hClient->GetAddr()) {
					return NULL;
				}
				// TODO: Update Pattern
				auto bonesDisp = reinterpret_cast<uint8_t*>(0x0);// hClient->ScanMemory(BONES_PTR_OFFSET_PATTERN);
				dwBonesOffset = hClient->ResolveDisp32(bonesDisp, 2);
				if (!dwBonesOffset)
					return NULL;
				printf("dwBonesOffset: 0x%p\n", dwBonesOffset);
			}
			return dwBonesOffset;
		}
	}
}