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


	delete config;

}