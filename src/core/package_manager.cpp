#include "core/package_manager.hpp"
#include "parser/brew_parser.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <cctype>
#include "logger/logger.hpp"

PackageManager &PackageManager::getInstance(std::shared_ptr<PackageManagerParser> parser)
{
    static PackageManager instance(parser);
    return instance;
}

PackageManager::PackageManager(std::shared_ptr<PackageManagerParser> parser) : _packageManagerParser(parser)
{
    if (!_packageManagerParser)
        _packageManagerParser = std::make_shared<BrewParser>();
}

bool PackageManager::isPackageInstalled(const std::string &package_name)
{
    auto command_result = System::isPackageInstalled(package_name);
    return handleCommandResult(command_result);
}

bool PackageManager::installPackage(const std::string &package_name)
{
    auto command_result = System::installPackage(package_name);
    return handleCommandResult(command_result);
}

bool PackageManager::upgradePackage(const std::string &package_name)
{
    auto command_result = System::upgradePackage(package_name);
    return handleCommandResult(command_result);
}

bool PackageManager::uninstallPackage(const std::string &package_name)
{
    auto command_result = System::uninstallPackage(package_name);
    return handleCommandResult(command_result);
}

std::vector<Package> PackageManager::searchPackages(const std::string &query)
{
    std::vector<Package> packages;
    auto command_result = System::searchPackages(query);

    if (handleCommandResult(command_result))
        _packageManagerParser->ParseSearchResult(command_result, packages);

    return packages;
}

std::vector<Package> PackageManager::listInstalledPackages()
{
    std::vector<Package> packages;
    auto command_result = System::listInstalledPackages();

    if (handleCommandResult(command_result))
        _packageManagerParser->ParseInstalled(command_result, packages);

    return packages;
}

Package PackageManager::getPackageInfo(const std::string &package_name)
{
    Package package(package_name);
    auto command_result = System::getPackageInfo(package_name);

    if (handleCommandResult(command_result))
        _packageManagerParser->ParseInfo(command_result, package);

    return package;
}

bool PackageManager::handleCommandResult(CommandResult &result)
{
    if (result.exit_code != 0)
    {
        Logger::getInstance().log(LOG_LVL::ERR, 
                   "Command: " + result.command + "\n" +
                   "Error executing command:\n" + result.output + "\n" +
                   "Exit code: " + std::to_string(result.exit_code) + "\n" +
                   result.error);

        return false;
    }

    Logger::getInstance().log(LOG_LVL::INF, 
               "Command: " + result.command + "\n" +
               "Command executed successfully:\n" + result.output + "\n" +
               result.error);

    return true;
}
