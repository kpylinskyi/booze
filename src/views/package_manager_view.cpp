#include "views/package_manager_view.hpp"
#include "core/package_manager.hpp"
#include "logger/logger.hpp"

PackageManagerView::PackageManagerView()
{
    auto installed_packages = PackageManager::getInstance().listInstalledPackages();
    for (auto& package : installed_packages){
        Logger::getInstance().log(LOG_LVL::INF, package.getName());
        _installedPackages.push_back(std::make_shared<PackageView>(package.getName()));
    }
}

std::vector<std::shared_ptr<PackageView>> PackageManagerView::search(const std::string &query)
{
    auto found_packages = PackageManager::getInstance().searchPackages(query);
    std::vector<std::shared_ptr<PackageView>> found_packages_views;
    for (auto& package : found_packages){
        found_packages_views.push_back(std::make_shared<PackageView>(package.getName()));
    }
    return found_packages_views;
}