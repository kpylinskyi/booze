#include "parser/package_manager_parser.hpp"
#include <sstream>

std::vector<std::string> PackageManagerParser::Split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}