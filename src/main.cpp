#include "core/package_manager.hpp"
#include <memory>
#include "gui/main_window.hpp"

int main(int argc, char **argv) {
    // auto pm = PackageManager(std::make_shared<System>());

    // pm.removePackage("git");
    // pm.installPackage("git");
    // pm.upgradePackage("git");
    // pm.listInstalledPackages();
    //
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<MainWindow>(argc, argv);
}
