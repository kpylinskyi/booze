#ifndef PACKAGE_MANAGER_CMD_H
#define PACKAGE_MANAGER_CMD_H

#include "core/cmd/cmd.h"

class PackageManagerCmd : public Cmd {
public:
    PackageManagerCmd(const std::string& command = "brew") : Cmd(command) {};

};

#endif //PACKAGE_MANAGER_CMD_H
