//
// Created by Octavian Custura on 08/05/2020.
//

#ifndef ASSIGNMENT_9_GUI_H
#define ASSIGNMENT_9_GUI_H
#include <QApplication>
#include "Service.h"
class GUI {
private:
	Service service;
	QApplication application;
public:
	GUI(int argc, char** argv, Service);
	int runProgram();
};



#endif //ASSIGNMENT_9_GUI_H
