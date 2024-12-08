#ifndef LIST_H
#define LIST_H

#include "core/cmd/pmcmd.h"

class ListCmd : public PackageManagerCmd {
  public:
    ListCmd(const std::string& command = "brew list") : PackageManagerCmd(command) {};
};

#endif //LIST_H
