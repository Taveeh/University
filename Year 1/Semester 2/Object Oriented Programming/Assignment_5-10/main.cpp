#include "GUI.h"
#include "TestFootage.h"
#include "TestMemoryRepository.h"
#include "TestService.h"
#include "TestFileRepository.h"
#include <QFileInfo>
#include <QDebug>
#include <iostream>
#include <QDir>
void callTestFunctions();
using namespace std;
int main(int argc, char** argv){
//	callTestFunctions();
	QApplication application(argc, argv);
	Service service = Service();
	GUI gui{service};
	gui.show();
	return application.exec();
}

void callTestFunctions() {
	TestFootage::test_all();
	TestMemoryRepository::test_all();
	TestService::test_all();
	TestFileRepository::test_all();
//	std::cout << "Tests finished\n";
}
