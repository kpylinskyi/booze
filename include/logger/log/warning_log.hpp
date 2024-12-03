#ifndef WARNINGLOG_HPP
#define WARNINGLOG_HPP

#include "logger/log/log.hpp"

class WarningLog: public Log {
public:
    WarningLog(std::string message);

    void print() const override;

private:
    const std::string _color_code;
};

#endif