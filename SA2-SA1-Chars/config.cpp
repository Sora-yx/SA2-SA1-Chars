#include "pch.h"

bool sonic = true;
bool miles = true;
bool knux = true;
bool amy = true;
bool ss = true;
bool SonicUpgrade = true;
bool milesUpgrade = true;
bool knuxUpgrade = true;
bool amyUpgrade = true;

extern "C" {

	__declspec(dllexport) bool isSA1Char(uint8_t charID)
	{
		switch (charID)
		{
		case Characters_Sonic:
		default:
			return sonic;
		case Characters_Tails:
			return miles;
		case Characters_Knuckles:
			return knux;
		case Characters_Amy:
			return amy;
		case Characters_SuperSonic:
			return ss;
		}
	}
}


void ReadConfig(const char* path) {

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	sonic = config->getBool("Characters", "sonic", true);
	miles = config->getBool("Characters", "miles", true);
	knux = config->getBool("Characters", "knux", true);
	amy = config->getBool("Characters", "amy", true);

	delete config;


	if (sonic)
		Sonic_Init();

	if (miles)
		Miles_Init();

	/**if (amy)
		Amy_Init();*/

}