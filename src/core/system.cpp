#include "core/system.hpp"
#include <boost/process.hpp>
#include <boost/process/error.hpp>
#include <iostream>
#include <sstream>

namespace bp = boost::process;

System::System()
{
}
bool System::populateConfig(const std::string &config_path) {}
bool System::isPackageInstalled(const std::string &package_name) {}
bool System::installPackage(const std::string &package_name) {}
bool System::updatePackage(const std::string &package_name) {}
bool System::removePackage(const std::string &package_name) {}
std::vector<std::string> System::searchPackages(const std::string &query) {}
std::vector<std::string> System::listInstalledPackages() {}
std::string System::getPackageStatus(const std::string &package_name) {}
bool System::refreshPackageDatabase() {}

std::string System::execute(const std::string &command)
{
    std::ostringstream output;

    try
    {
        bp::ipstream pipe_stream;
        bp::ipstream err_stream;
        bp::child process(command, bp::std_out > pipe_stream, bp::std_err > err_stream);

        std::string line;

        while (pipe_stream && std::getline(pipe_stream, line))
        {
            output << line << std::endl;
        }

        while (err_stream && std::getline(err_stream, line))
        {
            output << line << std::endl;
        }

        process.wait();
        if (process.exit_code() != 0)
        {
            output << "Command failed with exit code: " << process.exit_code() << std::endl;
        }
    }
    catch (const std::exception &ex)
    {
        output << "Errorr executing command " << command << ":\n" << ex.what() << std::endl;
    }
    return output.str();
}