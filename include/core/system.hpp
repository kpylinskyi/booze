#include <string>
#include <vector>
#include <unordered_map>

struct CommandResult {
    int exit_code;
    std::string stdout_str;
    std::string stderr_str;
};

class System {
public:
    System();

    bool installPackage(const std::string &package_name);
    bool upgradePackage(const std::string &package_name);
    bool uninstallPackage(const std::string &package_name);
    bool isPackageInstalled(const std::string &package_name);
    bool searchPackages(const std::string &query, std::string& results);
    bool listInstalledPackages(std::string& results);
    bool getPackageInfo(const std::string &package_name, std::string& results);

private:
    CommandResult execute(const std::string& command);
    bool handleCommandResult(const CommandResult &result, const std::string& command);
    bool executeAndHandle(const std::string &command);
    bool executeAndCapture(const std::string &command, std::string& output);
};