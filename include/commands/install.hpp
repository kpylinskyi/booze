#ifndef INSTALL_HPP
#define INSTALL_HPP

#include "commands/command.hpp"

class InstallCommand : public Command {
public:
    InstallCommand(const std::string& package_name, const std::string& install_command = "brew install")
        : Command(install_command + " " + package_name) {}
};

#endif
