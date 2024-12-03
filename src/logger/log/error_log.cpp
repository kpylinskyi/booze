#include "logger/log/error_log.hpp"
#include "logger/log_level.hpp"
#include <iostream>

ErrorLog::ErrorLog(std::string message): Log(message), _color_code("\033[1;31m") {};

void ErrorLog::print() const
{
    std::cout << _color_code << "[" << LogLevel::to_string(LOG_LVL::ERR) << "] " << _reset_color_code << to_string() << std::endl;
}
