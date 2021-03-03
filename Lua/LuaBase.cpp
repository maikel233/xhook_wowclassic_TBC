#include "stdafx.h"
#include "LuaBase.h"
#include "GameMethods.h"
//#include "../Pipes/Server.h"
#include "Settings/Settings.h"

#define LUA_PATH R"(C:\Xhook\wow\lua\lua.txt)"

vector<tuple<string, chrono::time_point<chrono::steady_clock>, bool> > LuaBase::Commands;

//void LuaBase::CheckPipes()
//{
//    if (Pipes::Server::Request.empty() || Pipes::Server::Request.find('@') != string::npos)
//        return;
//
//    auto request = Pipes::Server::Request;
//    Pipes::Server::Request = "";
//
//    if (request.find('(') != string::npos)
//    {
//        GameMethods::Execute(request);
//        Pipes::Server::Response = "Working...";
//        Pipes::Server::Cv.notify_one();
//    }
//    else
//    {
//        Pipes::Server::Response = GameMethods::GetText(request.c_str());
//        Pipes::Server::Cv.notify_one();
//    }
//}

void LuaBase::Execute()
{

    if (Commands.empty() || !GameMethods::ObjMgrIsValid(0))
        return;

    for (auto i = 0; i < Commands.size(); i++)
    {
        auto c = Commands[i];
        if (get<bool>(c) && chrono::high_resolution_clock::now() > get<chrono::time_point<chrono::steady_clock>>(c))
        {
            GameMethods::Execute(get<string>(c));
            auto size = Commands.size();
            Commands.erase(Commands.begin() + i);
            Commands.resize(size - 1);
        }
    }
}

void LuaBase::Input(string command, int64_t delayMS)
{
    auto t = make_tuple(command, chrono::high_resolution_clock::now() + chrono::duration<int64_t, milli>(delayMS), true);
    Commands.push_back(t);
}

void LuaBase::PushLua()
{
    string line;
    string lines = "\"";
    ifstream file(LUA_PATH);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            line = regex_replace(line, regex("^[ \t]+|[ \t]+$"), "$1");
            if (!line.empty())
                lines += line + " ";
        }
        file.close();
        lines = lines.substr(0, lines.length() - 1);
        lines += "\"";
    }

    Input("iterObjects(0)", 0);
    Input("f=loadstring(" + lines + ") f()", 0);
}