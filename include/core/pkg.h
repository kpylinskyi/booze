#ifndef PKG_H
#define PKG_H

#include "core/cmd/pkg/install.h"
#include "core/cmd/pkg/isinstalled.h"
#include "core/cmd/pkg/uninstall.h"
#include "core/cmd/pkg/upgrade.h"
#include "core/cmd/pkg/info.h"

#include <string>
#include <vector>
#include <memory>

/**
 * @enum PackageType
 * @brief Enum representing the type of a Homebrew package.
 */
enum class PackageType
{
    Formulae,
    Cask
};

class Package
{
    Package(const std::string &name);

    void install();
    void isinstalled();
    void uninstall();
    void upgrade();
    void info();

    const bool &getInstalled() const { installed_; }
    const PackageType &getType() const { type_; }
    const std::string &getName() const { name_; }
    const std::string &getInstalledVersion() const { installed_version_; }
    const std::string &getAvailableVersion() const { available_version_; }
    const std::string &getDescription() const { description_; }
    const std::string &getLicense() const { license_; }

private:
    bool installed_;
    PackageType type_;
    std::string name_;
    std::string installed_version_;
    std::string available_version_;
    std::string description_;
    std::string license_;
    std::vector<Package> dependencies_;

    std::unique_ptr<InstallCmd> install_cmd_;
    std::unique_ptr<IsInstalledCmd> isinstalled_cmd_;
    std::unique_ptr<UninstallCmd> uninstall_cmd_;
    std::unique_ptr<UpgradeCmd> upgrade_cmd_;
    std::unique_ptr<InfoCmd> info_cmd_;
};

#endif // PKG_H