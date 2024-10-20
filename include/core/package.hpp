// File: src/core/Package.h

#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <vector>

// Enum representing the package's current status
enum class PackageStatus {
    INSTALLED,
    AVAILABLE,
    OUTDATED,
    NOT_FOUND
};

class Package {
public:
    Package() = default;
    Package(const std::string& name, 
            const std::string& version = "unknown", 
            const std::vector<Package>& dependencies = {}, 
            PackageStatus status = PackageStatus::NOT_FOUND);

    std::string getName() const;
    std::string getVersion() const;
    std::vector<Package> getDependencies() const;
    PackageStatus getStatus() const;

    void setName(const std::string& name);
    void setVersion(const std::string& version);
    void setDependencies(const std::vector<Package>& dependencies);
    void setStatus(PackageStatus status);

private:
    std::string name;
    std::string version;
    std::vector<Package> dependencies;
    PackageStatus status;
};

#endif
