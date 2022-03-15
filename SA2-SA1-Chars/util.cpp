#include "pch.h"

bool isNewTrick() {
	HMODULE amyNT = GetModuleHandle(L"SA2-Amy-New-Tricks");

	if (amyNT)
		return true;

	return false;
}