#include "logger/log/info_log.hpp"
#include "logger/log_level.hpp"
#include <iostream>

InfoLog::InfoLog(std::string message) : Log(std::move(message)), _color_code("\033[94m")
{
}


void InfoLog::print() const
{
    std::cout << _color_code << "[" << LogLevel::to_string(LOG_LVL::INF) << "] " << _reset_color_code << to_string() << std::endl;
}