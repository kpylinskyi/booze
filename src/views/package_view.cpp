#include "views/package_view.hpp"
#include "core/package.hpp"
#include <iostream>
#include <sstream>
#include <iomanip> 

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

std::string PackageView::toString() const {
    std::ostringstream oss;
    oss << "+----------------------------------------+\n"
        << "|           PACKAGE DETAILS              |\n"
        << "+----------------------------------------+\n"
        << "| Name        : " << std::setw(25) << _name << "|\n"
        << "| Version     : " << std::setw(25) << _version << "|\n"
        << "| Description : " << std::setw(25) << _description.substr(0, 25) << "|\n"
        << "| License     : " << std::setw(25) << _license << "|\n"
        << "| Installed   : " << std::setw(25) << (_installed ? "Yes" : "No") << "|\n"
        << "+----------------------------------------+\n";

    if (_dependencies.empty()) {
        oss << "| Dependencies: None                     |\n";
    } else {
        oss << "| Dependencies:                          |\n";
        for (const auto &dependency : _dependencies) {
            oss << "|   - " << std::setw(30) << dependency.getName() << "|\n";
        }
    }
    oss << "+----------------------------------------+\n";

    return oss.str();
}
