#include "core/package.hpp"

Package::Package(
    const std::string& name, 
    const std::string& version = "unknown", 
    const std::vector<Package>& dependencies = {}, 
    PackageStatus status = PackageStatus::NOT_FOUND) { }
            
std::string Package::getName() const { return name; }
std::string Package::getVersion() const { return version; } 
std::vector<Package> Package::getDependencies() const { return dependencies;}
PackageStatus Package::getStatus() const { return status; }

void Package::setName(const std::string& name) { this->name = name; }
void Package::setVersion(const std::string& version) { this->version = version; }
void Package::setDependencies(const std::vector<Package>& dependencies) { this->dependencies = dependencies; }
void Package::setStatus(PackageStatus status) { this->status = status; }