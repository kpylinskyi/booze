#ifndef PACKAGE_MANAGER_HPP
#define PACKAGE_MANAGER_HPP

#include <memory>
#include <string>
#include <vector>
#include "core/package.hpp"
#include "core/system.hpp"

class PackageManager {
public:
    static PackageManager& getInstance();

    bool isPackageInstalled(const std::string& package_name);
    bool installPackage(const std::string& package_name);
    bool upgradePackage(const std::string& package_name);
    bool uninstallPackage(const std::string& package_name);

    std::vector<Package> searchPackages(const std::string& query);
    std::vector<Package> listInstalledPackages();

    Package getPackageInfo(const std::string& package_name);

    PackageManager(const PackageManager&) = delete;
    PackageManager& operator=(const PackageManager&) = delete;

private:
    PackageManager() {}

    bool handleCommandResult(CommandResult& result);

    void parsePackagesFromSection(const std::string& line, std::vector<Package>& packages, const std::string& package_type);
    void handlePackageSections(std::istringstream& stream, std::vector<Package>& packages);
    void parsePackageInfo(const std::string& output, Package& package);
};

#endif
