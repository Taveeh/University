#include "UI.h"
#include "GUI.h"
#include "TestFootage.h"
#include "TestMemoryRepository.h"
#include "TestService.h"
#include "TestFileRepository.h"
void callTestFunctions();
using namespace std;
int main(int argc, char** argv) {
//	callTestFunctions();
	Service service = Service();
	GUI gui(argc, argv, service);

//	UI ui = UI(service);
//	ui.runProgram();

	return gui.runProgram();
}

void callTestFunctions() {
	TestFootage::test_all();
	TestMemoryRepository::test_all();
	TestService::test_all();
	TestFileRepository::test_all();
//	std::cout << "Tests finished\n";
}
