#ifndef PACKAGE_MANAGER_VIEW_HPP
#define PACKAGE_MANAGER_VIEW_HPP

#include "core/package_manager.hpp"
#include "views/package_view.hpp"
#include <memory>

class PackageManagerView {
public:
    PackageManagerView();

    std::vector<std::shared_ptr<PackageView>> search(const std::string& query);
    inline std::vector<std::shared_ptr<PackageView>> list() const { return _installedPackages; }
 
private:
    std::vector<std::shared_ptr<PackageView>> _installedPackages;
};

#endif