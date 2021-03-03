#pragma once
#include <windows.h>
#include <Psapi.h>

#include <fstream>

#include "FindPattern.h"

DWORD FindPattern(std::string moduleName, std::string pattern);
