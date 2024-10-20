#include <string>
#include <vector>

class System {
public:
    System();

    bool populateConfig(const std::string &config_path);
    bool isPackageInstalled(const std::string &package_name);
    bool installPackage(const std::string &package_name);
    bool updatePackage(const std::string &package_name);
    bool removePackage(const std::string &package_name);
    std::vector<std::string> searchPackages(const std::string &query);
    std::vector<std::string> listInstalledPackages();
    std::string getPackageStatus(const std::string &package_name);
    bool refreshPackageDatabase();

private:
    std::string execute(const std::string &command);
};
