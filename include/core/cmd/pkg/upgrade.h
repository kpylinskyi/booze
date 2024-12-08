#ifndef UPGRADECMD_H
#define UPGRADECMD_H

#include "core/cmd/pkgcmd.h"

class UpgradeCmd : public PackageCmd {
  public:
    UpgradeCmd(const std::string& pkgname, const std::string& command = "brew upgrade") : PackageCmd(command + " " + pkgname) {};
};

#endif //UPGRADECMD_H
