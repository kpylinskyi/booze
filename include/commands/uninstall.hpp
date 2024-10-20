#ifndef UNINSTALL_HPP
#define UNINSTALL_HPP

#include "commands/command.hpp"

class UninstallCommand : public Command {
public:
    UninstallCommand(const std::string& package_name, const std::string& uninstall_command = "brew uninstall")
        : Command(uninstall_command + " " + package_name) {}
};

#endif
