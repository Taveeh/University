#include "UI.h"
#include "TestFootage.h"
#include "TestMemoryRepository.h"
#include "TestService.h"
#include "TestFileRepository.h"
void callTestFunctions();
using namespace std;
int main() {
	callTestFunctions();
	Service service = Service();
	UI ui = UI(service);
	ui.runProgram();
	return 0;
}

void callTestFunctions() {
	TestFootage::test_all();
	TestMemoryRepository::test_all();
	TestService::test_all();
	TestFileRepository::test_all();
//	std::cout << "Tests finished\n";
}
