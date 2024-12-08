#ifndef PACKAGE_CMD_H
#define PACKAGE_CMD_H

#include "core/cmd/cmd.h"

class PackageCmd : public Cmd {
	public:
    	PackageCmd(const std::string& command = "brew") : Cmd(command) {};

};

#endif //PACKAGE_CMD_H
