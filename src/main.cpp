#include "core/package_manager.hpp"
#include <iostream>

#include <iostream>
#include "core/package_manager.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <package_name>" << std::endl;
        return 1;
    }

    std::string package_name = argv[1];

    PackageManager& pm = PackageManager::getInstance();

    Package package = pm.getPackageInfo(package_name);

    std::cout << "Package Name: " << package.getName() << std::endl;
    std::cout << "Version: " << package.getVersion() << std::endl;
    std::cout << "Description: " << package.getDescription() << std::endl;
    std::cout << "License: " << package.getLicense() << std::endl;

    if (!package.getDependencies().empty()) {
        for (const auto& dep : package.getDependencies()) {
            std::cout << "Dependency: " << dep.getName() << ", Version: " << dep.getVersion() << std::endl;
        }
    } else {
        std::cout << "No dependencies found." << std::endl;
    }

    return 0;
}
