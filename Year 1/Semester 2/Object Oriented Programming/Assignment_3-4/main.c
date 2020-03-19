#include <stdio.h>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include "tests.h"

int main() {
    callTestFunctions();
    Repository* repository = createRepository();
    Service* service = createService(repository);
    UI* ui = createUI(service);
    readUserCommand(ui);
    destroyUI(ui);
    return 0;
}
