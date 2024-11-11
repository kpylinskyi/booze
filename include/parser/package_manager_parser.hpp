#ifndef PACKAGE_MANAGER_PARSER_HPP
#define PACKAGE_MANAGER_PARSER_HPP

#include "core/package.hpp"
#include "core/system.hpp"
#include <vector>
#include <string>

/**
 * @class PackageManagerParser
 * @brief Abstract base class for parsing package management command results, including installed packages, search results, and package details.
 */
class PackageManagerParser {
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived objects.
     */
    virtual ~PackageManagerParser() = default;

    /**
     * @brief Parses the result of an installed packages command.
     * @param command_result The command result containing installed packages information.
     * @param packages A vector to store the parsed installed packages.
     */
    virtual std::vector<Package> ParseInstalled(const CommandResult& command_result) = 0;

    /**
     * @brief Parses the result of a package search command.
     * @param command_result The command result containing search results.
     * @param packages A vector to store the parsed search result packages.
     */
    virtual std::vector<Package> ParseSearchResult(const CommandResult& command_result) = 0;

    /**
     * @brief Parses the result of a package information command.
     * @param command_result The command result containing package information.
     * @param package A Package object to store the parsed package information.
     */
    virtual Package ParseInfo(const CommandResult& command_result) = 0;

protected:
    /**
     * @brief Splits a string by a specified delimiter.
     * @param str The string to split.
     * @param delimiter The character used to delimit the substrings.
     * @return A vector of substrings resulting from the split operation.
     */
    std::vector<std::string> Split(const std::string &str, char delimiter);
};

#endif // PACKAGE_MANAGER_PARSER_HPP
