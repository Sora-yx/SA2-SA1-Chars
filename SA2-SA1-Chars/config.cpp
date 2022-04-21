#include "pch.h"

bool sonic = true;
bool miles = true;
bool knux = true;
bool amy = true;
bool SonicUpgrade = true;
bool milesUpgrade = true;
bool knuxUpgrade = true;
bool amyUpgrade = true;


void ReadConfig(const char* path) {

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	sonic = config->getBool("Sonic", "sonic", true);
	miles = config->getBool("Miles", "miles", true);
	knux = config->getBool("Knux", "knux", true);
	amy = config->getBool("Amy", "amy", true);

	delete config;


	if (sonic)
		Sonic_Init();

	if (miles)
		Miles_Init();

	if (amy)
		Amy_Init();

}