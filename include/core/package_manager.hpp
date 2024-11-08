#ifndef PACKAGE_MANAGER_HPP
#define PACKAGE_MANAGER_HPP

#include "core/package.hpp"
#include "core/system.hpp"
#include "parser/package_manager_parser.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * @class PackageManager
 * @brief Singleton class that manages package operations like install, upgrade, uninstall, and search.
 */
class PackageManager
{
public:
    /**
     * @brief Gets the singleton instance of PackageManager, initializing it if necessary.
     * @param parser An optional shared pointer to a PackageManagerParser object.
     * @return A reference to the singleton instance of PackageManager.
     */
    static PackageManager &getInstance(std::shared_ptr<PackageManagerParser> parser = nullptr);

    /**
     * @brief Checks if a specified package is installed.
     * @param package_name The name of the package to check.
     * @return True if the package is installed, false otherwise.
     */
    bool isPackageInstalled(const std::string &package_name);

    /**
     * @brief Installs the specified package.
     * @param package_name The name of the package to install.
     * @return True if the installation was successful, false otherwise.
     */
    bool installPackage(const std::string &package_name);

    /**
     * @brief Upgrades the specified package to the latest version.
     * @param package_name The name of the package to upgrade.
     * @return True if the upgrade was successful, false otherwise.
     */
    bool upgradePackage(const std::string &package_name);

    /**
     * @brief Uninstalls the specified package.
     * @param package_name The name of the package to uninstall.
     * @return True if the uninstallation was successful, false otherwise.
     */
    bool uninstallPackage(const std::string &package_name);

    /**
     * @brief Searches for packages matching the query.
     * @param query The search term for finding packages.
     * @return A vector of Package objects that match the query.
     */
    std::vector<Package> searchPackages(const std::string &query);

    /**
     * @brief Lists all installed packages.
     * @return A vector of Package objects representing all installed packages.
     */
    std::vector<Package> listInstalledPackages();

    /**
     * @brief Retrieves detailed information about a specified package.
     * @param package_name The name of the package to retrieve information for.
     * @return A Package object containing detailed information about the package.
     */
    Package getPackageInfo(const std::string &package_name);

    // Deleting copy constructor and assignment operator to enforce singleton pattern.
    PackageManager(const PackageManager &) = delete;
    PackageManager &operator=(const PackageManager &) = delete;

private:
    /**
     * @brief Private constructor for the singleton pattern, initializing with a parser.
     * @param parser A shared pointer to a PackageManagerParser object for parsing package information.
     */
    PackageManager(std::shared_ptr<PackageManagerParser> parser);

    std::shared_ptr<PackageManagerParser> _packageManagerParser; /**< Parser used to parse package data. */

    /**
     * @brief Handles the result of a command and checks for errors.
     * @param result The CommandResult object containing the command execution result.
     * @return True if the command was successful, false otherwise.
     */
    bool handleCommandResult(CommandResult &result);
};

#endif // PACKAGE_MANAGER_HPP