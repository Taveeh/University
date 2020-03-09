#include <stdio.h>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include <string.h>
#include <stdlib.h>
#include "UI.h"

void callTestFunctions() {
    testMap();
    testRepository();
    testService();
}

int main() {
    callTestFunctions();
    Repository repository = createRepository();
    Service service = createService(&repository);
    UI ui = createUI(&service);
    readUserCommand(&ui);
    return 0;
}
