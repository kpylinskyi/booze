#ifndef PACKAGE_MANAGER_HPP
#define PACKAGE_MANAGER_HPP

#include <string>
#include <vector>
#include "core/package.hpp"
#include "core/system.hpp"

class PackageManager{
public:
    PackageManager(std::shared_ptr<System> system);

    bool installPackage(const std::string& package_name);
    bool updatePackage(const std::string& package_name);
    bool removePackage(const std::string& package_name);

    std::vector<Package> searchPackages(const std::string& query);
    std::vector<Package> listInstalledPackages();

    PackageStatus getPackageStatus(const std::string& package_name);
    bool refreshPackageDatabase();

private:
    std::shared_ptr<System> system;
};

#endif