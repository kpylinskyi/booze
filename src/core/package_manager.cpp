#include "core/package_manager.hpp"
#include <iostream>
#include <sstream>
#include <regex>

PackageManager& PackageManager::getInstance() {
    static PackageManager instance;
    return instance;
}

bool PackageManager::isPackageInstalled(const std::string &package_name) {
    auto command_result = System::isPackageInstalled(package_name);
    return handleCommandResult(command_result);
}

bool PackageManager::installPackage(const std::string &package_name) {
    auto command_result = System::installPackage(package_name);
    return handleCommandResult(command_result);
}

bool PackageManager::upgradePackage(const std::string &package_name) {
    auto command_result = System::upgradePackage(package_name);
    return handleCommandResult(command_result);
}

bool PackageManager::uninstallPackage(const std::string &package_name) {
    auto command_result = System::uninstallPackage(package_name);
    return handleCommandResult(command_result);
}

std::vector<Package> PackageManager::searchPackages(const std::string &query) {
    std::vector<Package> packages;
    auto command_result = System::searchPackages(query);

    if (handleCommandResult(command_result)) {
        std::istringstream stream(command_result.output);
        handlePackageSections(stream, packages);
    }

    return packages;
}

std::vector<Package> PackageManager::listInstalledPackages() {
    std::vector<Package> packages;
    auto command_result = System::listInstalledPackages();

    if (handleCommandResult(command_result)) {
        std::istringstream stream(command_result.output);
        handlePackageSections(stream, packages);
    }

    return packages;
}

Package PackageManager::getPackageInfo(const std::string &package_name) {
    Package package;
    auto command_result = System::getPackageInfo(package_name);

    if (handleCommandResult(command_result)) {
        parsePackageInfo(command_result.output, package);
    }

    return package;
}

bool PackageManager::handleCommandResult(CommandResult &result) {
    if (result.exit_code != 0) {
        std::cerr << "Command: " << result.command << "\n"
                  << "Error executing command:\n"
                  << result.output << "\n"
                  << "Exit code: " << result.exit_code << "\n"
                  << result.error << std::endl;
        return false;
    }

    std::cout << "Command: " << result.command << "\n"
              << "Command executed successfully:\n"
              << result.output << "\n"
              << result.error << std::endl;
    return true;
}

// Helper function to parse packages from a section
void PackageManager::parsePackagesFromSection(const std::string &line, std::vector<Package> &packages, const std::string &package_type) {
    std::istringstream package_stream(line);
    std::string package_name;
    while (package_stream >> package_name) {
        packages.push_back(getPackageInfo(package_name));
    }
}

// Helper function to handle different sections of package listings (formulae/casks)
void PackageManager::handlePackageSections(std::istringstream &stream, std::vector<Package> &packages) {
    std::string line;
    bool in_formulae_section = false;
    bool in_casks_section = false;

    while (std::getline(stream, line)) {
        if (line.find("==> Formulae") != std::string::npos) {
            in_formulae_section = true;
            in_casks_section = false;
            continue;
        } else if (line.find("==> Casks") != std::string::npos) {
            in_formulae_section = false;
            in_casks_section = true;
            continue;
        }

        if (in_formulae_section && !line.empty()) {
            parsePackagesFromSection(line, packages, "formulae");
        } else if (in_casks_section && !line.empty()) {
            parsePackagesFromSection(line, packages, "cask");
        }
    }
}

// Helper function to parse package details from output
void PackageManager::parsePackageInfo(const std::string& output, Package& package) {
    std::istringstream stream(output);
    std::string line;
    std::regex name_version_regex(R"(==>\s*(\w+):\s*stable\s*([\d.]+))");
    std::regex license_regex(R"(License:\s*(.*))");
    std::regex dependencies_regex(R"(Required:\s*(.*))");
    std::regex installed_regex(R"((Not installed|Installed))");

    std::vector<std::string> dependencies;
    bool in_dependencies_section = false;

    while (std::getline(stream, line)) {
        std::smatch match;

        // Parse package name and version
        if (std::regex_search(line, match, name_version_regex)) {
            package.setName(match[1]);
            package.setVersion(match[2]);
            continue;
        }

        // Parse package description
        if (line.find("==>") == std::string::npos && !package.getDescription().empty()) {
            package.setDescription(package.getDescription() + line + " ");
        } else if (package.getDescription().empty() && line.find("==>") == std::string::npos) {
            package.setDescription(line);
        }

        // Parse installation status
        if (std::regex_search(line, match, installed_regex)) {
            package.setInstalled(match[1] == "Installed" ? true : false);
            continue;
        }

        // Parse license
        if (std::regex_search(line, match, license_regex)) {
            package.setLicense(match[1]);
            continue;
        }

        // Parse dependencies
        if (line.find("==> Dependencies") != std::string::npos) {
            in_dependencies_section = true;
            continue;
        }

        if (in_dependencies_section && std::regex_search(line, match, dependencies_regex)) {
            std::istringstream dep_stream(match[1]);
            std::string dependency;
            while (std::getline(dep_stream, dependency, ',')) {
                // Clean up special characters from dependencies
                std::string cleaned_dependency;
                for (char ch : dependency) {
                    if (ch != '✔' && ch != '✘') {
                        cleaned_dependency += ch;
                    }
                }
                dependencies.push_back(cleaned_dependency);
            }
            package.setDependencies(dependencies);
            in_dependencies_section = false;
        }
    }
}
