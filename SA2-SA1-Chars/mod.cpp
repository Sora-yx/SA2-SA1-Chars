#include "pch.h"

HelperFunctions HelperFunctionsGlobal;
const char* error = "[SA1 Chars]: WARNING: Your version of the Mod Loader is old, the mod won't work properly.\nPlease update your Mod Loader for the best experience.";


extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		Sleep(10);

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 8) {
			PrintDebug(error);
			MessageBoxA(MainWindowHandle, error, "SA1 Chars", MB_ICONWARNING);
		}

		ReadConfig(path); //get mod settings by the user
	}

	__declspec(dllexport) void __cdecl OnFrame() {



	}



	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}