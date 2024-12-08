#ifndef INSTALLCMD_H
#define INSTALLCMD_H

#include "core/cmd/pkgcmd.h"

class InstallCmd: public PackageCmd {
    public:
        InstallCmd(const std::string& pkgname, const std::string& command = "brew install") : PackageCmd(command + " " + pkgname) {};
};

#endif //INSTALLCMD_H
