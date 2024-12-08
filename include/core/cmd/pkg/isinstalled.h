#ifndef ISINSTALLED_H
#define ISINSTALLED_H

#include "core/cmd/pkgcmd.h"

class IsInstalledCmd : public PackageCmd {
    public:
      IsInstalledCmd(const std::string& pkgname, const std::string& command = "brew list | grep") : PackageCmd(command + " " + pkgname) {};
};

#endif //ISINSTALLED_H
