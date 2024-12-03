#ifndef LOG_LEVEL_HPP
#define LOG_LEVEL_HPP

#include <string>

enum class LOG_LVL
{
    INF,
    WRN,
    ERR,
};

class LogLevel {
public:
    static std::string to_string(LOG_LVL log_lvl);
};

#endif