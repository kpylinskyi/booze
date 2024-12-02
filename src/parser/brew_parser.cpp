#include "parser/brew_parser.hpp"
#include <sstream>
#include <regex>
#include <unordered_set>

void BrewParser::ParseInstalled(const CommandResult &command_result, std::vector<Package> &packages)
{
    ParsePackageList(command_result, packages);
};

void BrewParser::ParseSearchResult(const CommandResult &command_result, std::vector<Package> &packages)
{
    ParsePackageList(command_result, packages);
};

void BrewParser::ParseInfo(const CommandResult &command_result, Package &package)
{
    std::istringstream stream(command_result.output);
    std::string line;
    std::string version_pattern = "==> " + package.getName() + R"(:\s*(.*))";
    std::regex version_regex(version_pattern);
    std::regex from_regex(R"(From:\s*(.*))");
    std::regex license_regex(R"(License:\s*(.*))");
    std::regex dependencies_regex(R"(Required:\s*(.*))");

    std::vector<std::string> dependencies;
    bool in_description_section = false;

    while (std::getline(stream, line))
    {
        std::smatch match;

        if (std::regex_search(line, match, version_regex))
        {
            package.setVersion(match[1]);
            in_description_section = true;
            continue;
        }

        if (in_description_section)
        {
            bool installed = line == "Installed";
            bool not_installed = line == "Not installed";

            if (installed || not_installed)
            {
                package.setInstalled(installed);
                in_description_section = false;
            }
        }

        if (in_description_section)
            package.setDescription(package.getDescription() + "\n" + line);

        if (std::regex_search(line, match, license_regex))
        {
            package.setLicense(match[1]);
        }

        if (std::regex_search(line, match, dependencies_regex))
        {
            std::istringstream dep_stream(match[1]);
            std::string dependency;
            while (std::getline(dep_stream, dependency, ','))
            {
                std::string cleaned_dependency;
                const static std::unordered_set<char> allowed_chars{'-', '_', '.'};
                std::copy_if(dependency.begin(), dependency.end(), std::back_inserter(cleaned_dependency),
                             [](char ch)
                             { return std::isalnum(ch) || allowed_chars.count(ch); });

                dependencies.push_back(cleaned_dependency);
            }
            package.setDependencies(dependencies);
        }
    }
};

void BrewParser::ParsePackageList(const CommandResult &command_result, std::vector<Package> &packages)
{
    std::istringstream stream(command_result.output);
    std::string line;
    int section = 0;

    while (std::getline(stream, line))
    {
        if (line.empty())
            continue;

        if (line.find("==>") != std::string::npos)
        {
            if (line.find("Formulae") != std::string::npos)
            {
                section = 1;
            }
            else if (line.find("Casks") != std::string::npos)
            {
                section = 2;
            }
            continue;
        }

        if (section == 1 || section == 2)
        {
            std::vector<std::string> package_names = this->Split(line, '\t');

            for (const std::string &pkg_name : package_names)
            {
                packages.push_back({pkg_name});
            }
        }
    }
};