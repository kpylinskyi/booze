#include <string>
#include <vector>
#include <unordered_map>

struct CommandResult {
    int exit_code;
    std::string command;
    std::string output;
    std::string error;
};

class System {
public:
    static CommandResult installPackage(const std::string &package_name);
    static CommandResult upgradePackage(const std::string &package_name);
    static CommandResult uninstallPackage(const std::string &package_name);
    static CommandResult isPackageInstalled(const std::string &package_name);
    static CommandResult searchPackages(const std::string &query);
    static CommandResult listInstalledPackages();
    static CommandResult getPackageInfo(const std::string &package_name);

private:
    static CommandResult execute(const std::string& command);
};