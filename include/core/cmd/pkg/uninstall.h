#ifndef UNINSTALLCMD_H
#define UNINSTALLCMD_H

#include "core/cmd/pkgcmd.h"

class UninstallCmd : public PackageCmd {
    public:
      UninstallCmd(const std::string& pkgname, const std::string& command = "brew uninstall") : PackageCmd(command + " " + pkgname) {};
};

#endif //UNINSTALLCMD_H
