#include <string>
#include <vector>
#include <map>


struct CommandResult {
    int exit_code;
    std::string stdout_str;
    std::string stderr_str;
};

class System {
public:
    System();

    bool isPackageInstalled(const std::string &package_name);
    bool installPackage(const std::string &package_name);
    bool updatePackage(const std::string &package_name);
    bool removePackage(const std::string &package_name);
    std::vector<std::string> searchPackages(const std::string &query);
    std::vector<std::string> listInstalledPackages();
    std::string getPackageInfo(const std::string &package_name);

private:
    CommandResult execute(const std::string &command);
    bool fileExists(const std::string &path);
    bool createConfigDirectory(const std::string &path);
    bool initializeConfig();
    bool readConfig(const std::string &path);
    bool populateConfig(const std::string &path);

    std::string configDirectory;
    std::string configFileName;
    std::string configFilePath; 
    std::map<std::string, std::map<std::string, std::string>> packageManagers;
    std::string activePackageManager; 
};
