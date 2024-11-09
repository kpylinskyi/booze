#ifndef CORE_SYSTEM_HPP
#define CORE_SYSTEM_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <future>

/**
 * @struct CommandResult
 * @brief Represents the result of a system command execution.
 */
struct CommandResult {
    int exit_code;        /**< The exit code returned by the command. */
    std::string command;  /**< The command that was executed. */
    std::string output;   /**< Standard output of the command. */
    std::string error;    /**< Standard error output of the command, if any. */
};

/**
 * @class System
 * @brief Provides a set of static methods to interact with the system's package management commands for Homebrew.
 */
class System {
public:
    /**
     * @brief Installs a specified package.
     * @param package_name The name of the package to install.
     * @return A CommandResult struct containing the result of the install command.
     */
    static CommandResult installPackage(const std::string &package_name);

    /**
     * @brief Installs a specified package asynchronously.
     * @param package_name The name of the package to install.
     * @return A future that will contain the result of the install command once it completes.
     */
    static std::future<CommandResult> installPackageAsync(const std::string &package_name);

    /**
     * @brief Upgrades a specified package to the latest version.
     * @param package_name The name of the package to upgrade.
     * @return A CommandResult struct containing the result of the upgrade command.
     */
    static CommandResult upgradePackage(const std::string &package_name);

    /**
     * @brief Upgrades a specified package to the latest version asynchronously.
     * @param package_name The name of the package to upgrade.
     * @return A future that will contain the result of the upgrade command once it completes.
     */
    static std::future<CommandResult> upgradePackageAsync(const std::string &package_name);

    /**
     * @brief Uninstalls a specified package.
     * @param package_name The name of the package to uninstall.
     * @return A CommandResult struct containing the result of the uninstall command.
     */
    static CommandResult uninstallPackage(const std::string &package_name);

    /**
     * @brief Uninstalls a specified package asynchronously.
     * @param package_name The name of the package to uninstall.
     * @return A future that will contain the result of the uninstall command once it completes.
     */
    static std::future<CommandResult> uninstallPackageAsync(const std::string &package_name);

    /**
     * @brief Checks if a specified package is installed.
     * @param package_name The name of the package to check.
     * @return A CommandResult struct containing the result of the check command.
     */
    static CommandResult isPackageInstalled(const std::string &package_name);

    /**
     * @brief Checks if a specified package is installed asynchronously.
     * @param package_name The name of the package to check.
     * @return A future that will contain the result of the check command once it completes.
     */
    static std::future<CommandResult> isPackageInstalledAsync(const std::string &package_name);

    /**
     * @brief Searches for packages that match the query.
     * @param query The search term for finding packages.
     * @return A CommandResult struct containing the result of the search command.
     */
    static CommandResult searchPackages(const std::string &query);

    /**
     * @brief Searches for packages that match the query asynchronously.
     * @param query The search term for finding packages.
     * @return A future that will contain the result of the search command once it completes.
     */
    static std::future<CommandResult> searchPackagesAsync(const std::string &query);

    /**
     * @brief Lists all installed packages.
     * @return A CommandResult struct containing the result of the list installed packages command.
     */
    static CommandResult listInstalledPackages();

    /**
     * @brief Lists all installed packages asynchronously.
     * @return A future that will contain the result of the list installed packages command once it completes.
     */
    static std::future<CommandResult> listInstalledPackagesAsync();

    /**
     * @brief Retrieves detailed information about a specified package.
     * @param package_name The name of the package to retrieve information for.
     * @return A CommandResult struct containing the result of the information retrieval command.
     */
    static CommandResult getPackageInfo(const std::string &package_name);

    /**
     * @brief Retrieves detailed information about a specified package asynchronously.
     * @param package_name The name of the package to retrieve information for.
     * @return A future that will contain the result of the information retrieval command once it completes.
     */
    static std::future<CommandResult> getPackageInfoAsync(const std::string &package_name);

private:
    /**
     * @brief Executes a specified system command and captures the result.
     * @param command The command string to execute.
     * @return A CommandResult struct containing the command's output, error, and exit code.
     */
    static CommandResult execute(const std::string& command);
};

#endif // CORE_SYSTEM_HPP