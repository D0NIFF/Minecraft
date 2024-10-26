#ifndef LOG_H
#define LOG_H

#include <string>

namespace System {

class Log {
private:
    static std::string currentDateTime();
public:
    static void alert(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);
};

} // System

#endif //LOG_H
