#ifndef PACKAGE_MANAGER_HPP
#define PACKAGE_MANAGER_HPP

#include "core/package.hpp"
#include "core/system.hpp"
#include "parser/package_manager_parser.hpp"
#include <memory>
#include <string>
#include <vector>

class PackageManager
{
public:
    static PackageManager &getInstance(std::shared_ptr<PackageManagerParser> parser = nullptr);

    bool isPackageInstalled(const std::string &package_name);
    bool installPackage(const std::string &package_name);
    bool upgradePackage(const std::string &package_name);
    bool uninstallPackage(const std::string &package_name);

    std::vector<Package> searchPackages(const std::string &query);
    std::vector<Package> listInstalledPackages();

    Package getPackageInfo(const std::string &package_name);

    PackageManager(const PackageManager &) = delete;
    PackageManager &operator=(const PackageManager &) = delete;

private:
    PackageManager(std::shared_ptr<PackageManagerParser> parser);
    std::shared_ptr<PackageManagerParser> _packageManagerParser;

    bool handleCommandResult(CommandResult &result);
};

#endif
