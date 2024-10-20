#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <boost/process.hpp>
#include <boost/process/error.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace bp = boost::process;

class Command {
private:
    std::string cmd;

public:
    Command(const std::string& command) :cmd(command) {}

    std::string execute();
};

#endif