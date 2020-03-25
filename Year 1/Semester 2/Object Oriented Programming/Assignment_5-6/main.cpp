#include <iostream>
#include "UI.h"
#include "TestFootage.h"
#include "TestDynamicArray.h"
#include "TestRepository.h"
#include "TestService.h"
void callTestFunctions();
int main() {
    std::ios::sync_with_stdio(false);
    callTestFunctions();
    auto repository = Repository();
    auto service = Service(repository);
    auto Ui = UI(service);
    Ui.runProgram();
    return 0;
}

void callTestFunctions() {
    TestFootage::test_all();
    TestDynamicArray::test_all();
    TestRepository::test_all();
    TestService::test_all();
}