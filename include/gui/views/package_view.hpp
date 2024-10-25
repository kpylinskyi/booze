#include "core/package_manager.hpp"
#include <string>
#include <vector>

class PackageView
{
public:
    PackageView(const std::string &name);

    bool install();
    bool uninstall();
    bool upgrade();

    std::string getName() const { return _name; }
    std::string getVersion() const { return _version; }
    std::string getDescripttion() const { return _description; }
    std::string getLicense() const { return _license; }
    std::vector<PackageView> getDependencies();

private:
    PackageManager &_pm;

    bool initialize();

    bool _installed;
    std::string _name;
    std::string _version;
    std::string _description;
    std::string _license;
    std::vector<std::string> _dependency_names;
    std::vector<PackageView> _dependencies;
}