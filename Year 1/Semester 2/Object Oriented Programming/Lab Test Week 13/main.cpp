#include "Repository.h"
#include "Service.h"
#include "GUI.h"

#include <QtWidgets/QApplication>
int main(int argc, char *argv[]) 
{
	QApplication a(argc, argv);
	Repository Repository;
	Service Service(Repository);
	Service.readFromFile("cars.txt");
	GUI AppGUI(Service);
	AppGUI.show();
	return a.exec();

}