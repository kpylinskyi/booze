#ifndef SEARCH_H
#define SEARCH_H

#include "core/cmd/pmcmd.h"

class SearchCmd : public PackageManagerCmd
{
public:
  SearchCmd(const std::string &pkgname, const std::string &command = "brew search") : PackageManagerCmd(command + " " + pkgname) {};

  void update(const std::string &pkgname, const std::string &command = "brew search") { command_ = command + " " + pkgname; };
};

#endif // SEARCH_H
