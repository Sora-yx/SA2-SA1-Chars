#include "pch.h"

HelperFunctions HelperFunctionsGlobal;
const char* error = "[SA1 Chars]: WARNING: Your version of the Mod Loader is old, the mod won't work properly.\nPlease update your Mod Loader for the best experience.";

HMODULE SA2Anim = NULL;

extern "C" {


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		Sleep(12);

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 8) {
			PrintDebug(error);
			MessageBoxA(MainWindowHandle, error, "SA1 Chars", MB_ICONWARNING);
		}

		SA2Anim = GetModuleHandle(L"SA2-Anim-Break");

		if (!SA2Anim)
		{
			MessageBox(MainWindowHandle,
				L"Failed to load SA2-Anim-Break.dll, the mod won't work!", L"SA1 Characters: DLL not found!", MB_OK | MB_ICONERROR);
		}

		ReadConfig(path); //get mod settings by the user
		Disable_Jiggle();
		PatchAnimations();
		init_OnionBlur();



	}

	__declspec(dllexport) void __cdecl OnFrame() {



	}



	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}