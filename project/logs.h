#ifndef _GAME_CONTROL_KIT_LOGS_H
#define _GAME_CONTROL_KIT_LOGS_H

#include <iostream>
#include <string>

namespace controlkit
{
    class Logs
    {
    public:
        inline static void Error(const std::string& err) { std::cout << err << std::endl; }
    };
}

#endif // _GAME_CONTROL_KIT_LOGS_H
