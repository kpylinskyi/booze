#include "core/system.hpp"
#include <boost/process.hpp>
#include <boost/process/error.hpp>
#include <nlohmann/json.hpp>
#include <sys/stat.h> 
#include <fstream>
#include <iostream>
#include <sstream>

using json = nlohmann::json;
namespace bp = boost::process;

System::System() 
    : configDirectory(std::string(getenv("HOME")) + "/.config/booze"),
      configFileName("system.json"),
      configFilePath(configDirectory + '/' + configFileName) 
{
    initializeConfig();
}


bool System::fileExists(const std::string &path) {
    std::ifstream file(path);
    return file.good();
}
bool System::createConfigDirectory(const std::string &path){
    struct stat info;

    if (stat(path.c_str(), &info) != 0){
        if(mkdir(path.c_str(), 0755) == -1)  {
            std::cerr << "Error: Could not create directory " << path << std::endl;
            return false;
        }
    } else if (!(info.st_mode & S_IFDIR)) {
        std::cerr << "Error: Path exists but is not a directory: " << path << std::endl;
        return false;
    }

    return true;
}

bool System::initializeConfig() {
    if(!createConfigDirectory(configDirectory)) return false;

    if(!fileExists(configFilePath)) {
        std::cout << "Config file not found, creating default config..." << std::endl;
        if (!populateConfig(configFilePath)) {
            std::cerr << "Error: Failed to create default config." << std::endl;
            return false;
        }
    } else {
        std::cout << "Config file found, using existing configuration." << std::endl;
    }

    if(!readConfig(configFilePath)) {
        std::cerr <<  "Error: Could not read file " << configFilePath << std::endl;
        return false;
    }

    return true;
}

bool System::populateConfig(const std::string &path) {
    json defaultConfig = {
        {"package_manager", "brew"},
        {"managers", {
            {"brew", {
                {"install", "brew install"},
                {"update", "brew update"},
                {"remove", "brew uninstall"},
                {"search", "brew search"},
                {"list", "brew list"},
                {"info", "brew info"}
            }},
        }}
    };

    std::ofstream configFile(path);
    if (configFile.is_open()) {
        configFile << defaultConfig.dump(4); 
        configFile.close();
        return true;
    } else {
        std::cerr << "Error: Could not write default config to " << path << std::endl;
        return false;
    }
}


bool System::readConfig(const std::string &path) {
    std::ifstream config_file(path);
    if (!config_file.is_open()) {
        std::cerr << "Error: Unable to open config file at " << path << std::endl;
        return false;
    }

    json config_json;
    try {
        config_file >> config_json;
    } catch (const json::parse_error &err) {
        std::cerr << "Error: Failed to parse JSON config file: " << err.what() << std::endl;
        return false;
    }

    if (config_json.contains("package_manager")) {
        activePackageManager = config_json["package_manager"].get<std::string>();
    } else {
        std::cerr << "Error: 'package_manager' not specified in config" << std::endl;
        return false;
    }

    if (config_json.contains("managers")) {
        auto managers = config_json["managers"];
        for (auto& [manager_name, commands] : managers.items()) {
            std::map<std::string, std::string> command_map;
            for (auto& [command_name, command_value] : commands.items()) {
                command_map[command_name] = command_value.get<std::string>();
            }
            packageManagers[manager_name] = command_map;
        }
    } else {
        std::cerr << "Error: 'managers' section not found in config" << std::endl;
        return false;
    }

    return true;
}

bool System::isPackageInstalled(const std::string &package_name) { 
    std::string isInstalledCommand = packageManagers[activePackageManager]["list"] + " | grep " + package_name;
    CommandResult result = execute(isInstalledCommand);

    return false;
}

bool System::installPackage(const std::string &package_name) {
    std::string installCommand = packageManagers[activePackageManager]["install"] + " " + package_name;
    CommandResult result = execute(installCommand);

    if (result.exit_code == 0) {
        std::cout << result.stdout_str << "Package installed successfully.\n";
        return true;
    } else {
        std::cerr << "Failed to install package:\n" << result.stderr_str;
        return false;
    }
}

bool System::updatePackage(const std::string &package_name) {
    std::string updateCommand = packageManagers[activePackageManager]["update"] + " " + package_name;
    CommandResult result = execute(updateCommand);

    if (result.exit_code == 0) {
        std::cout << result.stdout_str << "Package updated successfully.\n";
        return true;
    } else {
        std::cerr << "Failed to update package:\n" << result.stderr_str;
        return false;
    }
}

bool System::removePackage(const std::string &package_name) {
    std::string removeCommand = packageManagers[activePackageManager]["remove"] + " " + package_name;
    CommandResult result = execute(removeCommand);

    if (result.exit_code == 0) {
        std::cout << result.stdout_str << "Package removed successfully.\n";
        return true;
    } else {
        std::cerr << "Failed to remove package:\n" << result.stderr_str;
        return false;
    }
}

std::vector<std::string> System::searchPackages(const std::string &query) {
    std::string searchCommand = packageManagers[activePackageManager]["search"];
    CommandResult result = execute(searchCommand);

    std::vector<std::string> results;

    return results;
}
std::vector<std::string> System::listInstalledPackages() {
    std::string listCommand = packageManagers[activePackageManager]["list"];
    CommandResult result = execute(listCommand);

    std::vector<std::string> results;

    return results;
}

std::string System::getPackageInfo(const std::string &package_name) {
    std::string infoCommand = packageManagers[activePackageManager]["info"];
    CommandResult result = execute(infoCommand);

    if (result.exit_code == 0) {
        std::cout << result.stdout_str << "Package info fetched successfully.\n";
        return result.stdout_str;
    } else {
        std::cerr << "Failed to fetch package info:\n" << result.stderr_str;
        return result.stderr_str;
    }
}

CommandResult System::execute(const std::string &command) {
    std::ostringstream output;
    std::ostringstream error;

    try {
        bp::ipstream pipe_stream;
        bp::ipstream err_stream;
        bp::child process(command, bp::std_out > pipe_stream, bp::std_err > err_stream);

        std::string line;

        while (pipe_stream && std::getline(pipe_stream, line)) {
            output << line << '\n';
        }

        while (err_stream && std::getline(err_stream, line)) {
            error << line << '\n';
        }

        process.wait();
        return {process.exit_code(), output.str(), error.str()};
    } catch (const std::exception &ex) {
        return {-1, "", "Error executing command: " + std::string(ex.what())};
    }
}