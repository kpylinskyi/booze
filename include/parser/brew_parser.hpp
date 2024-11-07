#ifndef BREW_PARSER_HPP
#define BREW_PARSER_HPP

#include "parser/package_manager_parser.hpp"

class BrewParser: public PackageManagerParser {
public:
    BrewParser() {};

    void ParseInstalled(const CommandResult& command_result, std::vector<Package>& packages) override final;
    void ParseSearchResult(const CommandResult& command_result, std::vector<Package>& packages) override final;
    void ParseInfo(const CommandResult& command_result, Package &package) override final;

private:
    void ParsePackageList(const CommandResult& command_result, std::vector<Package>& packages);
};

#endif