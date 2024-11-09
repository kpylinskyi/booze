#include "core/package_manager.hpp"
#include "parser/brew_parser.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <cctype>

PackageManager &PackageManager::getInstance()
{
    static PackageManager instance(std::make_shared<BrewParser>());
    return instance;
}

PackageManager::PackageManager(std::shared_ptr<PackageManagerParser> parser) : _packageManagerParser(parser) {}

bool PackageManager::isPackageInstalled(const std::string &package_name)
{
    return executeSyncTask([&]()
                           { return System::isPackageInstalled(package_name); });
}

std::future<bool> PackageManager::isPackageInstalledAsync(const std::string &package_name)
{
    return executeAsyncTask("is_installed_" + package_name, [&]()
                            { return System::isPackageInstalledAsync(package_name); });
}

bool PackageManager::installPackage(const std::string &package_name)
{
    return executeSyncTask([&]()
                           { return System::installPackage(package_name); });
}

std::future<bool> PackageManager::installPackageAsync(const std::string &package_name)
{
    return executeAsyncTask("install_" + package_name, [&]()
                            { return System::installPackageAsync(package_name); });
}

bool PackageManager::upgradePackage(const std::string &package_name)
{
    return executeSyncTask([&]()
                           { return System::upgradePackage(package_name); });
}

std::future<bool> PackageManager::upgradePackageAsync(const std::string &package_name)
{
    return executeAsyncTask("upgrade_" + package_name, [&]()
                            { return System::upgradePackageAsync(package_name); });
}

bool PackageManager::uninstallPackage(const std::string &package_name)
{
    return executeSyncTask([&]()
                           { return System::uninstallPackage(package_name); });
}

std::future<bool> PackageManager::uninstallPackageAsync(const std::string &package_name)
{
    return executeAsyncTask("uninstall_" + package_name, [&]()
                            { return System::uninstallPackageAsync(package_name); });
}

std::vector<Package> PackageManager::searchPackages(const std::string &query)
{
    std::vector<Package> packages;
    auto command_result = System::searchPackages(query);

    if (handleCommandResult(command_result))
        _packageManagerParser->ParseSearchResult(command_result, packages);

    return packages;
}

std::future<std::vector<Package>> PackageManager::searchPackagesAsync(const std::string &query)
{
    return std::async(std::launch::async, [this, query]()
                      {
        std::vector<Package> packages;
        auto command_result = System::searchPackages(query);

        if (handleCommandResult(command_result)) {
            _packageManagerParser->ParseSearchResult(command_result, packages);
        }

        return packages; });
}

std::vector<Package> PackageManager::listInstalledPackages()
{
    std::vector<Package> packages;
    auto command_result = System::listInstalledPackages();

    if (handleCommandResult(command_result))
        _packageManagerParser->ParseInstalled(command_result, packages);

    return packages;
}

std::future<std::vector<Package>> PackageManager::listInstalledPackagesAsync()
{
    return std::async(std::launch::async, [this]()
                      {
        std::vector<Package> packages;
        auto command_result = System::listInstalledPackages();

        if (handleCommandResult(command_result)) {
            _packageManagerParser->ParseInstalled(command_result, packages);
        }

        return packages; });
}

Package PackageManager::getPackageInfo(const std::string &package_name)
{
    Package package(package_name);
    auto command_result = System::getPackageInfo(package_name);

    if (handleCommandResult(command_result))
        _packageManagerParser->ParseInfo(command_result, package);

    return package;
}

std::future<Package> PackageManager::getPackageInfoAsync(const std::string &package_name)
{
    return std::async(std::launch::async, [this, package_name]()
                      {
        Package package(package_name);
        auto command_result = System::getPackageInfo(package_name);

        if (handleCommandResult(command_result)) {
            _packageManagerParser->ParseInfo(command_result, package);
        }

        return package; });
}

bool PackageManager::handleCommandResult(CommandResult &result)
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

template <typename Func>
bool PackageManager::executeSyncTask(Func &&func)
{
    CommandResult command_result = func();
    return handleCommandResult(command_result);
}

template <typename Func>
std::future<bool> PackageManager::executeAsyncTask(const std::string &task_id, Func &&func)
{
    tasks[task_id] = func();
    return std::async(std::launch::async, [this, task_id]()
                      {
            CommandResult command_result = tasks[task_id].get();
            return handleCommandResult(command_result); });
}