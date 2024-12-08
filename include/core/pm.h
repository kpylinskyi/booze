#ifndef PM_H
#define PM_H

#include "core/cmd/pm/list.h"
#include "core/cmd/pm/search.h"
#include "core/pkg.h"

#include <string>
#include <vector>
#include <memory>

class PackageManager
{
public:
    PackageManager();

    void list();
    const std::vector<std::unique_ptr<Package>> &search(const std::string pkg_name);

    const std::vector<std::unique_ptr<Package>> &getInstalled() const { return installed_pkgs_; };

private:
    std::vector<std::unique_ptr<Package>> installed_pkgs_;

    std::unique_ptr<ListCmd> list_cmd_;
    std::unique_ptr<SearchCmd> search_cmd_;
};

#endif // PM_H