#include "core/system.hpp"
#include <boost/process.hpp>
#include <boost/process/v1/error.hpp>
#include <iostream>
#include <sstream>

namespace bp = boost::process;

CommandResult System::installPackage(const std::string &package_name)
{
    return execute("brew install " + package_name);
}

std::future<CommandResult> System::installPackageAsync(const std::string &package_name)
{
    return std::async(std::launch::async, execute, "brew install " + package_name);
}

CommandResult System::upgradePackage(const std::string &package_name)
{
    return execute("brew upgrade " + package_name);
}

std::future<CommandResult> System::upgradePackageAsync(const std::string &package_name)
{
    return std::async(std::launch::async, execute, "brew upgrade " + package_name);
}

CommandResult System::uninstallPackage(const std::string &package_name)
{
    return execute("brew uninstall " + package_name);
}

std::future<CommandResult> System::uninstallPackageAsync(const std::string &package_name)
{
    return std::async(std::launch::async, execute, "brew uninstall " + package_name);
}

CommandResult System::isPackageInstalled(const std::string &package_name)
{
    return execute("brew list | grep " + package_name);
}

std::future<CommandResult> System::isPackageInstalledAsync(const std::string &package_name)
{
    return std::async(std::launch::async, execute, "brew list | grep " + package_name);
}

CommandResult System::searchPackages(const std::string &query)
{
    return execute("brew search " + query);
}

std::future<CommandResult> System::searchPackagesAsync(const std::string &query)
{
    return std::async(std::launch::async, execute, "brew search " + query);
}

CommandResult System::listInstalledPackages()
{
    return execute("brew list");
}

std::future<CommandResult> System::listInstalledPackagesAsync()
{
    return std::async(std::launch::async, execute, "brew list");
}

CommandResult System::getPackageInfo(const std::string &package_name)
{
    return execute("brew info " + package_name);
}

CommandResult System::execute(const std::string &command)
{
    std::ostringstream output;
    std::ostringstream error;

    try
    {
        bp::ipstream pipe_stream;
        bp::ipstream err_stream;
        bp::child process(command, bp::std_out > pipe_stream, bp::std_err > err_stream);

        std::string line;
        while (std::getline(pipe_stream, line))
            output << line << '\n';
        while (std::getline(err_stream, line))
            error << line << '\n';

        process.wait();
        return {process.exit_code(), command, output.str(), error.str()};
    }
    catch (const std::exception &ex)
    {
        return {-1, command, "", "Error executing command: " + std::string(ex.what())};
    }
}