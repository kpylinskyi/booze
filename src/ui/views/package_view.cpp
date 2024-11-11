#include "ui/views/package_view.hpp"
#include "core/package.hpp"
#include <iostream>
#include <future>
#include <chrono>

PackageView::PackageView(const std::string &name, int depth) : _pm(PackageManager::getInstance()) {
    if (!initialize(name, depth)) std::cerr << "Error: unable to initialize PackageView";
}

bool PackageView::initialize(const std::string &name, int depth) {
    // Start time measurement
    auto start_time = std::chrono::high_resolution_clock::now();

    auto result = _pm.getPackageInfo(name);
    const auto package = result.get();

    _installed = package.getInstalled();
    _name = package.getName();
    _version = package.getVersion();
    _description = package.getDescription();
    _license = package.getLicense();
    _dependencyNames = package.getDependencies();
    if (depth > 0) {
        for (const auto& dependencyName : _dependencyNames) {
            _dependencies.push_back(PackageView(dependencyName, depth - 1));
        }
    }

    // End time measurement
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to initialize PackageView: " << duration << " ms" << std::endl;

    return true;
}

bool PackageView::install() {
    auto result = _pm.installPackage(_name);
    return result.get();
}

bool PackageView::uninstall() {
    auto result = _pm.uninstallPackage(_name);
    return result.get();
}

bool PackageView::upgrade() {
    auto result = _pm.upgradePackage(_name);
    return result.get();
}