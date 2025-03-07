#ifndef BREW_PARSER_HPP
#define BREW_PARSER_HPP

#include "parser/package_manager_parser.hpp"

/**
 * @class BrewParser
 * @brief Implements parsing functionality specific to Homebrew, handling command results for installed packages, search results, and package information.
 */
class BrewParser : public PackageManagerParser {
public:
    /**
     * @brief Default constructor for BrewParser.
     */
    BrewParser() {};

    /**
     * @brief Parses the result of an installed packages command.
     * @param command_result The command result containing installed packages information.
     * @param packages A vector to store the parsed installed packages.
     */
    void ParseInstalled(const CommandResult& command_result, std::vector<Package>& packages) override final;

    /**
     * @brief Parses the result of a package search command.
     * @param command_result The command result containing search results.
     * @param packages A vector to store the parsed search result packages.
     */
    void ParseSearchResult(const CommandResult& command_result, std::vector<Package>& packages) override final;

    /**
     * @brief Parses the result of a package information command.
     * @param command_result The command result containing package information.
     * @param package A Package object to store the parsed package information.
     */
    void ParseInfo(const CommandResult& command_result, Package &package) override final;

private:
    /**
     * @brief Parses a general list of packages from a command result.
     * @param command_result The command result containing a package list.
     * @param packages A vector to store the parsed packages.
     */
    void ParsePackageList(const CommandResult& command_result, std::vector<Package>& packages);
};

#endif // BREW_PARSER_HPP