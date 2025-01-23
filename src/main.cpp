#include "core/package_manager.hpp"
#include "views/package_view.hpp"
#include <iostream>
#include "logger/logger.hpp"
#include <QtWidgets>

int main(int argc, char **argv) {
//    if (argc < 2) {
//        std::cerr << "Usage: " << argv[0] << " <package_name>" << std::endl;
//        return 1;
//    }
//
//    Logger::getInstance().log(LOG_LVL::INF, "Yoy");
//    Logger::getInstance().log(LOG_LVL::WRN, "Yoy");
//    Logger::getInstance().log(LOG_LVL::ERR, "Yoy");
//
//    std::string package_name = argv[1];
//
//    auto pkg = PackageView(package_name);
//
//    std::cout << "Package Name: " << pkg.getName() << std::endl;
//    std::cout << "Version: " << pkg.getVersion() << std::endl;
//    std::cout << "Description: " << pkg.getDescription() << std::endl;
//    std::cout << "License: " << pkg.getLicense() << std::endl;
//
//    if (!pkg.getDependencies().empty()) {
//        for (const auto& dep : pkg.getDependencies()) {
//            std::cout << "Dependency: " << dep.getName() << ", Version: " << dep.getVersion() << std::endl;
//        }
//    } else {
//        std::cout << "No dependencies found." << std::endl;
//    }
//
//    return 0;

	QApplication app(argc, argv);
    QWidget window;
    window.resize(800, 600);
    window.show();
    window.setWindowTitle(QApplication::translate("toplevel", "Booze QT6 test build"));
    return app.exec();
}
