#include <iostream>
#include "UI.h"
int main() {
    std::ios::sync_with_stdio(false);
    testFoo();
    auto repo = Repository();
    auto serv = Service(repo);
    auto Ui = UI(serv);
    Ui.runProgramAdministrator();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
