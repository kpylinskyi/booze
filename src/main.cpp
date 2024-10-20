#include "commands/install.hpp"
#include "commands/uninstall.hpp"

int main() {
    auto install_command = InstallCommand("git");
    std::cout << install_command.execute() << std::endl;
    auto uninstall_command = UninstallCommand("git");
    std::cout << uninstall_command.execute() << std::endl;

    return 0;
}
