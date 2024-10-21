#include "core/package_manager.hpp"
#include <memory>

int main() {
    auto pm = PackageManager(std::make_shared<System>());

    pm.removePackage("git");
    pm.installPackage("git");
    pm.upgradePackage("git");
    pm.listInstalledPackages();

    return 0;
}
