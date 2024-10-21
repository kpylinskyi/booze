#include "core/package_manager.hpp"

PackageManager::PackageManager(std::shared_ptr<System> system) : system(system) {}

bool PackageManager::installPackage(const std::string& package_name) {
    return system->installPackage(package_name);
}

bool PackageManager::upgradePackage(const std::string& package_name) {
    return system->upgradePackage(package_name);
}

bool PackageManager::removePackage(const std::string& package_name) {
    return system->removePackage(package_name);
}

std::vector<Package> PackageManager::searchPackages(const std::string& query) {
    std::vector<Package> packages;
    std::vector<std::string> system_output = system->searchPackages(query);
    // Parse system_output and populate packages as needed
    return packages;
}

std::vector<Package> PackageManager::listInstalledPackages() {
    std::vector<Package> packages;
    std::vector<std::string> system_output = system->listInstalledPackages();
    // Parse system_output and populate packages as needed
    return packages;
}

PackageStatus PackageManager::getPackageInfo(const std::string& package_name) {
    std::string system_output = system->getPackageInfo(package_name);
    // Process system_output and return the correct PackageStatus
    return PackageStatus::NOT_FOUND;  // Example return value
}
