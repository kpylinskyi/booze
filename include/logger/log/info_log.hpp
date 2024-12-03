#ifndef INFOLOG_HPP
#define INFOLOG_HPP

#include "logger/log/log.hpp"

class InfoLog: public Log {
public:
    InfoLog(std::string message);

    void print() const override;

private:
    const std::string _color_code;
};

#endif