#pragma once
#include "stdafx.h"

class LuaBase
{
    static vector<tuple<string, chrono::time_point<chrono::steady_clock>, bool> > Commands;
public:
  //  static void CheckPipes();
    static void Execute();
    static void Input(std::string, int64_t);
    static void PushLua();
};