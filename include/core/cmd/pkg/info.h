#ifndef INFO_H
#define INFO_H

#include "core/cmd/pkgcmd.h"

class InfoCmd : public PackageCmd {
  public:
    InfoCmd(const std::string& pkgname, const std::string& command = "brew info") : PackageCmd(command + " " + pkgname) {};
};

#endif //INFO_H
