#pragma once
#include <GlobalData/Include.h>
#include <CS2/Patterns.h>
#include <string>


namespace CS2 {

	class CGameTraceManager;
	class CGameResourceService;
	class CMaterialSystem2;
	class CCSGOInput;
	class CPanoramaUIEngine;
	class CSchemaSystem;
	class CLegacyGameUI;
	class CSource2Client;
	class CCSGO_Hud;
	class CInterfaceManager {
	private:
		template <typename T>
		using CreateInterfaceFn = T * (__thiscall*)(const char* interfaceName, int unknown);

	public:
		inline static CGameResourceService* pGameResourceService = nullptr;
		inline static CPanoramaUIEngine* pPanoramaUIEngine = nullptr;

		inline static CGameTraceManager* pGameTraceManager = nullptr;
		inline static CCSGOInput* pCsGoInput = nullptr;

		inline static CMaterialSystem2* pMaterialSystem = nullptr;
		inline static CSchemaSystem* pSchemaSystem = nullptr;
		inline static CLegacyGameUI* pLegacyGameUI = nullptr;
		inline static CSource2Client* pSource2Client = nullptr;

		inline static CCSGO_Hud* pCsGoHud = nullptr;

		template <typename T>
		inline static T* CreateInterface(std::string module, std::string interfaceName) {
			auto m = ::Globals::pProc->GetRemoteModule(module);
			auto fn = (CInterfaceManager::CreateInterfaceFn<T>)m->GetProcAddress("CreateInterface");
			return (T*)fn(interfaceName.c_str(), NULL);
		}

		inline static void Initialize() {
			auto pClient = ::Globals::pProc->GetRemoteModule("client.dll");

			pGameTraceManager = ::Globals::pProc->ReadDirect<CGameTraceManager*>(
				pClient->ResolveRIP(
					pClient->ScanMemory(C_GAME_TRACE_MANAGER_PATTERN)
					, 0x3, 0x7)
			);

			pCsGoInput = reinterpret_cast<CCSGOInput*>(
				::Globals::pProc->ReadDirect<uintptr_t>(
					pClient->ResolveRIP(
						pClient->ScanMemory(C_CSGO_INPUT_PATTERN), 0x3, 0x7)
				)
				);

			// TODO: update pattern
			/*pCsGoHud = ::Globals::pProc->ReadDirect<CCSGO_Hud*>(
				pClient->ResolveRIP(
					pClient->ScanMemory(CCSGO_HUD_PATTERN)
					, 3, 7)
			);*/

			pGameResourceService = CreateInterface<CGameResourceService>("engine2.dll", "GameResourceServiceClientV001");
			pMaterialSystem = CreateInterface<CMaterialSystem2>("materialsystem2.dll", "VMaterialSystem2_001");
			pPanoramaUIEngine = CreateInterface<CPanoramaUIEngine>("panorama.dll", "PanoramaUIEngine001");
			pSchemaSystem = CreateInterface<CSchemaSystem>("schemasystem.dll", "SchemaSystem_001");
			pLegacyGameUI = CreateInterface<CLegacyGameUI>("client.dll", "LegacyGameUI001");
			pSource2Client = CreateInterface<CSource2Client>("client.dll", "Source2Client002");


			LogAll();
		}

		static void LogAll();
	};

	using I = CInterfaceManager;

}