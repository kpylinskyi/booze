#include "views/package_view.hpp"
#include "core/package.hpp"
#include <iostream>

PackageView::PackageView(const std::string &name, int depth) : _pm(PackageManager::getInstance()) {
    if (!initialize(name, depth)) std::cerr << "Error: unable to initialize PackageView";
}

bool PackageView::initialize(const std::string &name, int depth) {
    const auto package = _pm.getPackageInfo(name);
    
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
    return true;
}

bool PackageView::install() {
    return _pm.installPackage(_name);
}

bool PackageView::uninstall() {
    return _pm.uninstallPackage(_name);
}

bool PackageView::upgrade() {
    return _pm.upgradePackage(_name);
}