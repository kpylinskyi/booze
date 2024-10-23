#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <vector>

enum class PackageStatus {
    INSTALLED,
    NOT_INSTALLED
};

class Package {
public:
    Package() = default;

    void setName(const std::string& name) { _name = name; }
    void setVersion(const std::string& version) { _version = version; }
    void setDescription(const std::string& description) { _description = description; }
    void setLicense(const std::string& license) { _license = license; }
    void setStatus(PackageStatus status) { _status = status; }
    void setDependencies(const std::vector<Package>& dependencies) { _dependencies = dependencies; }

    std::string getName() const { return _name; }
    std::string getVersion() const { return _version; }
    std::string getDescription() const { return _description; }
    std::string getLicense() const { return _license; }
    std::vector<Package> getDependencies() const { return _dependencies; }
    PackageStatus getStatus() const { return _status; }

private:
    std::string _name;
    std::string _version;
    std::string _description;
    std::string _license;
    std::vector<Package> _dependencies;
    PackageStatus _status;
};

#endif
