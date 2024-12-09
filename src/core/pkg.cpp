#include "core/pkg.h"
#include "core/tasks.h"

#include <iostream>
#include <chrono>
#include <thread>

Package::Package(const std::string &name)
    : name_(name), installed_(false), type_(PackageType::Undefined) {}

void Package::install()
{
    if (!install_cmd_)
        install_cmd_ = std::make_unique<InstallCmd>(name_);

    Tasks::getInstance().addCmdTask(std::move(install_cmd_->execute()));
}

void Package::isinstalled()
{
    if (!isinstalled_cmd_)
        isinstalled_cmd_ = std::make_unique<IsInstalledCmd>(name_);

    Tasks::getInstance().addCmdTask(std::move(isinstalled_cmd_->execute()));
}

void Package::uninstall()
{
    if (!uninstall_cmd_)
        uninstall_cmd_ = std::make_unique<UninstallCmd>(name_);

    Tasks::getInstance().addCmdTask(std::move(uninstall_cmd_->execute()));
}

void Package::upgrade()
{
    if (!upgrade_cmd_)
        upgrade_cmd_ = std::make_unique<UpgradeCmd>(name_);

    Tasks::getInstance().addCmdTask(std::move(upgrade_cmd_->execute()));
}

void Package::info()
{
    if (!info_cmd_)
        info_cmd_ = std::make_unique<InfoCmd>(name_);
    
    Tasks::getInstance().addCmdTask(std::move(info_cmd_->execute()));
}