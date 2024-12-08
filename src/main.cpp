#include "core/package_manager.hpp"
#include "views/package_manager_view.hpp"
#include "logger/logger.hpp"
#include <memory>
#include <iostream>

int main() {

    auto pm_view = std::make_shared<PackageManagerView>();
    for(auto pkg: pm_view->list()){
        Logger::getInstance().log(LOG_LVL::INF, pkg->toString());
    }

    return 0;
}
