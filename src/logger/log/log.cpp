#include "logger/log/log.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

Log::Log(std::string message)
    : _message(std::move(message)), _timestamp(std::time(nullptr)), _reset_color_code("\033[0m")
{
}

std::string Log::to_string() const
{
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&_timestamp));

    std::ostringstream oss;
    oss << "[" << buffer << "] " << _message;
    return oss.str();
}
