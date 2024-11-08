#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <vector>

/**
 * @enum PackageType
 * @brief Enum representing the type of a Homebrew package.
 */
enum class PackageType {
    Formulae,
    Cask
};

/**
 * @class Package
 * @brief Represents a Homebrew package with relevant details and attributes.
 */
class Package {
public:
    /**
     * @brief Default constructor for the Package class.
     */
    Package() = default;

    /**
     * @brief Constructor that initializes a package with a name.
     * @param name The name of the package.
     */
    Package(const std::string& name);

    /**
     * @brief Sets the type of the package.
     * @param type The type of the package (Formulae or Cask).
     */
    void setType(PackageType type) { _type = type; }

    /**
     * @brief Sets the name of the package.
     * @param name The name of the package.
     */
    void setName(const std::string& name) { _name = name; }

    /**
     * @brief Sets the version of the package.
     * @param version The version of the package.
     */
    void setVersion(const std::string& version) { _version = version; }

    /**
     * @brief Sets the description of the package.
     * @param description The description of the package.
     */
    void setDescription(const std::string& description) { _description = description; }

    /**
     * @brief Sets the license of the package.
     * @param license The license of the package.
     */
    void setLicense(const std::string& license) { _license = license; }

    /**
     * @brief Sets the installation status of the package.
     * @param installed True if the package is installed, false otherwise.
     */
    void setInstalled(bool installed) { _insalled = installed; }

    /**
     * @brief Sets the dependencies of the package.
     * @param dependencies A vector of dependency package names.
     */
    void setDependencies(const std::vector<std::string>& dependencies) { _dependencies = dependencies; }

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
     * @brief Gets the license of the package.
     * @return The license of the package.
     */
    std::string getLicense() const { return _license; }

    /**
     * @brief Gets the dependencies of the package.
     * @return A vector of dependency package names.
     */
    std::vector<std::string> getDependencies() const { return _dependencies; }

    /**
     * @brief Gets the installation status of the package.
     * @return True if the package is installed, false otherwise.
     */
    bool getInstalled() const { return _insalled; }

private:
    PackageType _type;                     /**< The type of the package (Formulae or Cask). */
    std::string _name;                     /**< The name of the package. */
    std::string _version;                  /**< The version of the package. */
    std::string _description;              /**< The description of the package. */
    std::string _license;                  /**< The license of the package. */
    std::vector<std::string> _dependencies;/**< The dependencies of the package. */
    bool _insalled;                        /**< True if the package is installed, false otherwise. */
};

#endif
