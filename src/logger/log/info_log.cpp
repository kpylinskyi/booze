#include "logger/log/info_log.hpp"
#include <iostream>

InfoLog::InfoLog(std::string message) : Log(std::move(message)), _color_code("\033[94m")
{
}


void InfoLog::print() const
{
    std::cout << _color_code << "[INF] " << _reset_color_code << to_string() << std::endl;
}