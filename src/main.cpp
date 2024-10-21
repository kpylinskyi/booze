#include "core/system.hpp"

int main() {
    auto system = System();

    system.installPackage("git");

    return 0;
}
