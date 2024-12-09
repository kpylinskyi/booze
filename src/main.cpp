#include "core/pkg.h"
#include "core/tasks.h"

#include <iostream>

int main() {
    Package pkg("nano");

    pkg.isinstalled();
    if (!pkg.getInstalled()) {
        std::cout << "Package " << pkg.getName() << " is not installed. Installing...\n";
        pkg.install();
    }
    pkg.info();
    
    if (pkg.getInstalledVersion() != pkg.getAvailableVersion()) {
        std::cout << "Upgrading " << pkg.getName() << " to version " << pkg.getAvailableVersion() << "...\n";
        pkg.upgrade();
    }

    std::cout << "Uninstalling " << pkg.getName() << "...\n";
    pkg.uninstall();

    while(true){
        Tasks::getInstance().processPendingTasks();
    }

    return 0;
}
