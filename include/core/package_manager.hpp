#ifndef PACKAGE_MANAGER_HPP
#define PACKAGE_MANAGER_HPP

#include <memory> 
#include <string>
#include <vector>
#include "core/package.hpp"
#include "core/system.hpp"

class PackageManager{
public:
    PackageManager(std::shared_ptr<System> system);

    bool isPackageInstalled(const std::string& package_name);
    bool installPackage(const std::string& package_name);
    bool upgradePackage(const std::string& package_name);
    bool uninstallPackage(const std::string& package_name);

    std::vector<Package> searchPackages(const std::string& query);
    std::vector<Package> listInstalledPackages();

    Package getPackageInfo(const std::string& package_name);

private:
    std::shared_ptr<System> system;
};

#endif