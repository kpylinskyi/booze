#include "logger/log/warning_log.hpp"
#include "logger/log_level.hpp"
#include <iostream>

WarningLog::WarningLog(std::string message): Log(message), _color_code("\033[1;33m") {};

void WarningLog::print() const
{
    std::cout << _color_code << "[" << LogLevel::to_string(LOG_LVL::WRN) << "] " << _reset_color_code << to_string() << std::endl;
}
