#ifndef PACKAGE_MANAGER_PARSER_HPP
#define PACKAGE_MANAGER_PARSER_HPP

#include "core/package.hpp"
#include "core/system.hpp"
#include <vector>
#include <string>

class PackageManagerParser {
public:
    virtual void ParseInstalled(const CommandResult& command_result, std::vector<Package>& packages) = 0;
    virtual void ParseSearchResult(const CommandResult& command_result, std::vector<Package>& packages) = 0;
    virtual void ParseInfo(const CommandResult& command_result, Package &package) = 0;

protected:
    std::vector<std::string> Split(const std::string &str, char delimiter);
};

#endif