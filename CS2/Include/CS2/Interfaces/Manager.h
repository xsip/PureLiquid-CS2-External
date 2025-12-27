#pragma once
#include <GlobalData/Include.h>
#include <CS2/Patterns.h>
#include <string>


namespace CS2 {

	class CGameTraceManager;
	class CGameResourceService;
	class CCSGOInput;
	class CInterfaceManager {
	private:
		template <typename T>
		using CreateInterfaceFn = T * (__thiscall*)(const char* interfaceName, int unknown);

	public:
		inline static CGameResourceService* pGameResourceService = nullptr;

		inline static CGameTraceManager* pGameTraceManager = nullptr;
		inline static CCSGOInput* pCsGoInput = nullptr;

		template <typename T>
		inline static T* CreateInterface(std::string module, std::string interfaceName) {
			auto m = ::Globals::proc.GetRemoteModule(module);
			auto fn = (CInterfaceManager::CreateInterfaceFn<T>)m->GetProcAddress("CreateInterface");
			return (T*)fn(interfaceName.c_str(), NULL);
		}

		inline static void Initialize() {
			auto pClient = ::Globals::proc.GetRemoteModule("client.dll");

			pGameTraceManager = ::Globals::proc.ReadDirect<CGameTraceManager*>(
				pClient->ResolveRIP(
					pClient->ScanMemory(C_GAME_TRACE_MANAGER_PATTERN)
					, 0x3, 0x7)
			);

			pCsGoInput = reinterpret_cast<CCSGOInput*>(
				::Globals::proc.ReadDirect<uintptr_t>(
					pClient->ResolveRIP(
						pClient->ScanMemory(C_CSGO_INPUT_PATTERN), 0x3, 0x7)
				)
				);

			pGameResourceService = CreateInterface<CGameResourceService>("engine2.dll", "GameResourceServiceClientV001");



			LogAll();
		}

		inline static void LogAll() {
			printf("[+] Interfaces\n");
			printf("[+] CGameTraceManager: 0x%p\n", pGameTraceManager);
			printf("[+] CCSGOInput: 0x%p\n", pCsGoInput);
			printf("[+] CGameResourceService: 0x%p\n\n", pGameResourceService);
		}
	};

	using I = CInterfaceManager;

}