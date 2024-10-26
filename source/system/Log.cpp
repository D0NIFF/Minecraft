#pragma once
#include "Log.h"

#include <iostream>
#include <ctime>

namespace System {
    std::string Log::currentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

        return buf;
    }

    void Log::alert(const std::string& message)
    {
        std::cout << "[" << Log::currentDateTime() << "] " << message << std::endl;
    }

    void Log::error(const std::string& message)
    {
        std::cerr << "[" << Log::currentDateTime() << "] " << message << std::endl;
    }

    void Log::warn(const std::string& message)
    {
        std::cerr << "[" << Log::currentDateTime() << "] " << message << std::endl;
    }
} // System