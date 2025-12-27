#include <External/Include.h>
#include <Source2/CBaseHandle.h>
#include <CS2/SDK/client/CCSPlayerController.hpp>
#include <CS2/ExtendedSDK/scenesystem/CAnimatableSceneObjectDesc.h>
#include <CS2/ExtendedSDK/client/C_CSPlayerPawn.h>
#include <CS2/Interfaces/Include.h>
#include <Features/Aimbot.h>

namespace Globals {
	Process proc{ "cs2.exe" };
}

using namespace Globals;
using namespace CS2;


void ReadEntititesThread() {
	int bone = 0;
	auto pGameEntitySystem = CS2::I::pGameResourceService->GetGameEntitySystem();

	while (true) {
		for (int i = 1; i < 65; i++) {

			bool isLocalPlayer = i == 1;
			
			auto entity = &CS2::CGameEntitySystem::vEntityList[i];
			auto pController = pGameEntitySystem->GetEntityByIndex<CS2::client::CCSPlayerController>(i);

			if (!pController) {
				entity->m_bIsValid = false;
				continue;
			}

			if (!pController->m_hPawn.IsValid()) {
				entity->m_bIsValid = false;
				continue;
			}

			auto pPawn = pGameEntitySystem->GetEntityByIndex<CS2::client::C_CSPlayerPawnExtended>(pController->m_hPawn.GetEntryIndex());

			if (!pPawn) {
				entity->m_bIsValid = false;
				continue;
			}

			auto health = pPawn->m_iHealth;
			entity->m_bIsAlive = health > 0 && health <= pPawn->m_iMaxHealth;
			entity->m_bIsValid = true;
			entity->m_bIsLocalPlayer = isLocalPlayer;
			entity->m_iPawnIndex = pController->m_hPawn.GetEntryIndex();
			entity->m_pController = pController;
			entity->m_pPawn = pPawn;

		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main() {
	
	SetConsoleTitle("PureLiquid CS2 External");
	
	I::Initialize();
	
#ifdef USE_CHAMS
	auto hLatexChamsMaterial = I::pMaterialSystem->CreateMaterial(CMaterialSystem2::GetLatexChams(), "LatexChamsMaterial");

	if (!hLatexChamsMaterial) {
		printf("Couldn't create Material!!\n");
		return 0;
	}

	if (!CAnimatableSceneObjectDesc::InstallRendererHook(nullptr)) {
		printf("Error Installing CAnimatableSceneObjectDesc hook!!\n");
		return 0;
	}

	CAnimatableSceneObjectDesc::SetChamsColor(0, 35, 255, 255);
	CAnimatableSceneObjectDesc::SetChamsMaterial(hLatexChamsMaterial);
	CAnimatableSceneObjectDesc::SetChamsEnabled(true);
#endif
	I::pCsGoInput->HookCreateMove();
	
	std::thread([]() {ReadEntititesThread();}).detach();
	std::thread([]() {Aimbot::AimbotThread();}).detach();

	while (!GetAsyncKeyState(VK_DELETE)) {

		if (!GetAsyncKeyState(VK_LSHIFT)) {
			Sleep(500);
			continue;
		}
		printf("CMD: 0x%p\n", I::pCsGoInput->GetExecutionData().cmd);

	}

	I::pCsGoInput->UnhookCreateMove();
#ifdef USE_CHAMS
	CAnimatableSceneObjectDesc::UninstallRendererHook();
#endif
	return 1;
	std::thread([]() {ReadEntititesThread();}).detach();
	std::thread([]() {Aimbot::AimbotThread();}).detach();

	auto pGameEntitySystem = I::pGameResourceService->GetGameEntitySystem();

	auto lpController = pGameEntitySystem->GetEntityByIndex<CS2::client::CCSPlayerController>(1);
	auto lpPawn = pGameEntitySystem->GetEntityByIndex<CS2::client::C_CSPlayerPawnExtended>(lpController->m_hPawn.GetEntryIndex());
	
	while (!GetAsyncKeyState(VK_DELETE)) {

		if (!GetAsyncKeyState(VK_LSHIFT)) {
			Sleep(500);
			continue;
		}

		system("cls");
		for (int i = 1; i < 65; i++) {
			auto entity = &CGameEntitySystem::vEntityList[i];

			if (!entity->m_bIsValid || !entity->m_bIsAlive)
				continue;

			if (!entity->m_pPawn)
				continue;


			if (entity->m_bIsLocalPlayer)
				continue;


			printf("Entity %i: %s\n", i, I::pGameTraceManager->IsPlayerVisible(lpPawn, entity->m_pPawn) ? "Visible" : "Invisible");

		}
	}
	return 0;
}