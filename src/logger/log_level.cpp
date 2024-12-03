#include "logger/log_level.hpp"

std::string LogLevel::to_string(LOG_LVL log_lvl)
{
    switch (log_lvl)
    {
    case LOG_LVL::INF:
        return "INF";
    case LOG_LVL::WRN:
        return "WRN";
    case LOG_LVL::ERR:
        return "ERR";
    default:
        return "LOG";
    }
}
