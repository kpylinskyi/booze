#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <vector>

enum class PackageType {
    Formulae,
    Cask
};

class Package {
public:
    Package() = default;
    Package(const std::string& name);

    void setType(PackageType type) { _type = type; }
    void setName(const std::string& name) { _name = name; }
    void setVersion(const std::string& version) { _version = version; }
    void setDescription(const std::string& description) { _description = description; }
    void setLicense(const std::string& license) { _license = license; }
    void setInstalled(bool installed) { _insalled = installed; }
    void setDependencies(const std::vector<std::string>& dependencies) { _dependencies = dependencies; }

    std::string getName() const { return _name; }
    std::string getVersion() const { return _version; }
    std::string getDescription() const { return _description; }
    std::string getLicense() const { return _license; }
    std::vector<std::string> getDependencies() const { return _dependencies; }
    bool getInstalled() const { return _insalled; }

private:
    PackageType _type;
    std::string _name;
    std::string _version;
    std::string _description;
    std::string _license;
    std::vector<std::string> _dependencies;
    bool _insalled;
};

#endif
