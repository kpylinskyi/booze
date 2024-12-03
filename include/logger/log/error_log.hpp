#ifndef ERRORLOG_HPP
#define ERRORLOG_HPP

#include "logger/log/log.hpp"

class ErrorLog: public Log {
public:
    ErrorLog(std::string message);

    void print() const override;

private:
    const std::string _color_code;
};

#endif