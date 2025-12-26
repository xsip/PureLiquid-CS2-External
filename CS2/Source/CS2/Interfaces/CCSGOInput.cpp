#include <CS2/Interfaces/CCSGOInput.h>
#include <CS2/Patterns.h>
#include <Math/Vector.h>
#include <GlobalData/Include.h>
using namespace Globals;

namespace CS2 {


	uintptr_t CCSGOInput::ResolveViewAnglesOffset() {
		if (!pViewAnglesOffset) {
			auto hClient = ::Globals::proc.GetRemoteModule("client.dll");
			if (!hClient || hClient && !hClient->GetAddr()) {
				return NULL;
			}
			auto pViewAngleOffsetDisp = hClient->ScanMemory(C_CSGO_INPUT_VIEW_ANGLES_PATTERN);
			pViewAnglesOffset = hClient->ResolveDisp32(pViewAngleOffsetDisp,3);
			if (!pViewAnglesOffset)
				return NULL;
		}

		return pViewAnglesOffset;
	}
}