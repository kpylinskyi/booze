#include "core/package_manager.hpp"
#include "core/thread_pool.hpp"
#include "parser/brew_parser.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <cctype>

PackageManager& PackageManager::getInstance()
{
    static PackageManager instance(std::make_shared<BrewParser>());
    return instance;
}

PackageManager::PackageManager(std::shared_ptr<PackageManagerParser> parser)
    : _packageManagerParser(parser)
{
}

std::future<bool> PackageManager::isPackageInstalled(const std::string& package_name)
{
    return ThreadPool::getInstance().enqueue(
        [package_name, this]()
        {
            CommandResult result = System::isPackageInstalled(package_name);
            return handleCommandResult(result);
        });
}

std::future<bool> PackageManager::installPackage(const std::string& package_name)
{
    return ThreadPool::getInstance().enqueue(
        [package_name, this]()
        {
            CommandResult result = System::installPackage(package_name);
            return handleCommandResult(result);
        });
}

std::future<bool> PackageManager::upgradePackage(const std::string& package_name)
{
    return ThreadPool::getInstance().enqueue(
        [package_name, this]()
        {
            CommandResult result = System::upgradePackage(package_name);
            return handleCommandResult(result);
        });
}

std::future<bool> PackageManager::uninstallPackage(const std::string& package_name)
{
    return ThreadPool::getInstance().enqueue(
        [package_name, this]()
        {
            CommandResult result = System::uninstallPackage(package_name);
            return handleCommandResult(result);
        });
}

std::future<std::vector<Package>> PackageManager::searchPackages(const std::string& query)
{
    return ThreadPool::getInstance().enqueue(
        [query, this]()
        {
            CommandResult result = System::searchPackages(query);
            return _packageManagerParser->ParseSearchResult(result);
        });
}

std::future<std::vector<Package>> PackageManager::listInstalledPackages()
{
    return ThreadPool::getInstance().enqueue(
        [this]()
        {
            CommandResult result = System::listInstalledPackages();
            return _packageManagerParser->ParseInstalled(result);
        });
}

std::future<Package> PackageManager::getPackageInfo(const std::string& package_name)
{
    return ThreadPool::getInstance().enqueue(
        [package_name, this]()
        {
            CommandResult result = System::getPackageInfo(package_name);
            return _packageManagerParser->ParseInfo(result);
        });
}

bool PackageManager::handleCommandResult(CommandResult& result)
{
    if (result.exit_code != 0)
    {
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
};