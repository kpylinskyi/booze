#include "core/system.hpp"
#include <boost/process.hpp>
#include <boost/process/error.hpp>
#include <iostream>
#include <sstream>

namespace bp = boost::process;

System::System() {}

bool System::installPackage(const std::string &package_name)
{
    return executeAndHandle("brew install " + package_name);
}

bool System::upgradePackage(const std::string &package_name)
{
    return executeAndHandle("brew upgrade " + package_name);
}

bool System::uninstallPackage(const std::string &package_name)
{
    return executeAndHandle("brew uninstall " + package_name);
}

bool System::isPackageInstalled(const std::string &package_name)
{
    std::string results;
    bool success = executeAndCapture("brew list | grep " + package_name, results);
    
    return success && results.find(package_name) != std::string::npos ? true : false;
}

bool System::searchPackages(const std::string &query, std::string& results)
{
    return executeAndCapture("brew search " + query, results);
}

bool System::listInstalledPackages(std::string& results)
{
    return executeAndCapture("brew list", results);
}

bool System::getPackageInfo(const std::string &package_name, std::string& results)
{
    return executeAndCapture("brew info " + package_name, results);
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
        while (std::getline(pipe_stream, line)) output << line << '\n';
        while (std::getline(err_stream, line)) error << line << '\n';

        process.wait();
        return {process.exit_code(), output.str(), error.str()};
    }
    catch (const std::exception &ex)
    {
        return {-1, "", "Error executing command: " + std::string(ex.what())};
    }
}

bool System::handleCommandResult(const CommandResult &result, const std::string &command)
{
    if (result.exit_code != 0)
    {
        std::cerr << "Command: " << command << "\n"
                  << "Error executing command:\n"
                  << result.stdout_str << "\n"
                  << "Exit code: " << result.exit_code << "\n"
                  << result.stderr_str << std::endl;
        return false;
    }

    std::cout << "Command: " << command << "\n"
              << "Command executed successfully:\n"
              << result.stdout_str << result.stderr_str << std::endl;
    return true;
}

bool System::executeAndHandle(const std::string &command)
{
    CommandResult result = execute(command);
    return handleCommandResult(result, command);
}

bool System::executeAndCapture(const std::string &command, std::string& output)
{
    CommandResult result = execute(command);
    if (result.exit_code == 0) output = result.stdout_str;
    return handleCommandResult(result, command);
}
