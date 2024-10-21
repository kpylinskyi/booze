#include "core/package_manager.hpp"

PackageManager::PackageManager(std::shared_ptr<System> system) : system(system) {}

bool PackageManager::installPackage(const std::string& package_name) {
    return system->installPackage(package_name);
}

bool PackageManager::updatePackage(const std::string& package_name) {
    return system->updatePackage(package_name);
}

bool PackageManager::removePackage(const std::string& package_name) {
    return system->removePackage(package_name);
}

std::vector<Package> PackageManager::searchPackages(const std::string& query) {
    std::vector<Package> packages;
    std::vector<std::string> system_output = system->searchPackages(query);
    return packages;
}

std::vector<Package> PackageManager::listInstalledPackages() {
    std::vector<Package> packages;
    std::vector<std::string> system_output = system->listInstalledPackages();
    return packages;
}

PackageStatus PackageManager::getPackageStatus(const std::string& package_name) {
    PackageStatus package_status;
    std::string system_output = system->getPackageStatus(package_name);
    return package_status;
}