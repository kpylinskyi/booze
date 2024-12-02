#ifndef PACKAGE_VIEW_HPP
#define PACKAGE_VIEW_HPP

#include "core/package_manager.hpp"
#include <string>
#include <vector>

/**
 * @class PackageView
 * @brief Provides a view and interface for interacting with Homebrew packages, allowing installation, uninstallation, and upgrade.
 */
class PackageView
{
public:
    /**
     * @brief Constructs a PackageView object with the specified package name and dependency depth.
     * @param name The name of the package to represent.
     * @param depth The level of dependency depth to retrieve, default is 1.
     */
    PackageView(const std::string &name, int depth = 1);

    /**
     * @brief Installs the package represented by this view.
     * @return True if the installation was successful, false otherwise.
     */
    bool install();

    /**
     * @brief Uninstalls the package represented by this view.
     * @return True if the uninstallation was successful, false otherwise.
     */
    bool uninstall();

    /**
     * @brief Upgrades the package to the latest version.
     * @return True if the upgrade was successful, false otherwise.
     */
    bool upgrade();

    /**
     * @brief Gets the installation status of the package.
     * @return True if the package installed, false otherwise.
     */
    bool getInstalled() const { return _installed; }

    /**
     * @brief Gets the name of the package.
     * @return The name of the package.
     */
    std::string getName() const { return _name; }

    /**
     * @brief Gets the version of the package.
     * @return The version of the package.
     */
    std::string getVersion() const { return _version; }

    /**
     * @brief Gets the description of the package.
     * @return The description of the package.
     */
    std::string getDescription() const { return _description; }

    /**
     * @brief Gets the license type of the package.
     * @return The license of the package.
     */
    std::string getLicense() const { return _license; }

    /**
     * @brief Gets the list of dependencies for this package.
     * @return A vector of PackageView objects representing the package dependencies.
     */
    std::vector<PackageView> getDependencies() const { return _dependencies; }

private:
    PackageManager &_pm;                      /**< Reference to the PackageManager instance to manage packages. */

    /**
     * @brief Initializes the package with the specified name and retrieves its dependencies up to a given depth.
     * @param name The name of the package to initialize.
     * @param depth The dependency depth to retrieve.
     * @return True if initialization was successful, false otherwise.
     */
    bool initializeAsync(const std::string &name, int depth = 1);
    bool initializeSync(const std::string &name, int depth = 1);

    bool _installed;                          /**< Installation status of the package. */
    std::string _name;                        /**< The name of the package. */
    std::string _version;                     /**< The version of the package. */
    std::string _description;                 /**< The description of the package. */
    std::string _license;                     /**< The license of the package. */
    std::vector<std::string> _dependencyNames;/**< Names of dependencies for the package. */
    std::vector<PackageView> _dependencies;   /**< List of dependencies as PackageView objects. */
};

#endif // PACKAGE_VIEW_HPP