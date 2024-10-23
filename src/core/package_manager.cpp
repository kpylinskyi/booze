#include "core/package_manager.hpp"

PackageManager::PackageManager(std::shared_ptr<System> system) : system(system) {}

bool PackageManager::isPackageInstalled(const std::string& package_name){
    return system->isPackageInstalled(package_name);
}

bool PackageManager::installPackage(const std::string& package_name) {
    return system->installPackage(package_name);
}

bool PackageManager::upgradePackage(const std::string& package_name) {
    return system->upgradePackage(package_name);
}

bool PackageManager::uninstallPackage(const std::string& package_name) {
    return system->uninstallPackage(package_name);
}

std::vector<Package> PackageManager::searchPackages(const std::string& query) {
    std::vector<Package> packages;
    std::string system_output;
    if (system->searchPackages(query, system_output)) {
        // Parse system_output and populate packages as needed
    }
    return packages;
}

std::vector<Package> PackageManager::listInstalledPackages() {
    std::vector<Package> packages;
    std::string system_output;
    if (system->listInstalledPackages(system_output)) {
        // Parse system_output and populate packages as needed
    }
    return packages;
}

Package PackageManager::getPackageInfo(const std::string& package_name) {
    std::string system_output;

    if (system->getPackageInfo(package_name, system_output)){
        // Parse system_output and populate package
    }
    return Package();
}
