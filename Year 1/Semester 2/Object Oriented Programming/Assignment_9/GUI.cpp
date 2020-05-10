//
// Created by Octavian Custura on 08/05/2020.
//

#include "GUI.h"
#include <QtWidgets>
GUI::GUI(int argc, char **argv, Service newService):application(argc, argv), service(newService) {
	auto* main = new QWidget();
	main->show();
	main->setWindowTitle("Movie application");
	QHBoxLayout *boxLayout = new QHBoxLayout();
	main->setLayout(boxLayout);

	QWidget* details = new QWidget();
	QFormLayout *formLayout = new QFormLayout();
	details->setLayout(formLayout);
	QLabel *labelName = new QLabel("&Name");
	QLineEdit* textBoxName = new QLineEdit();
	labelName->setBuddy(textBoxName);
	formLayout->addRow(labelName, textBoxName);
	QLabel *labelAge = new QLabel("&Age");
	QLineEdit *textBoxAge = new QLineEdit();
	labelAge->setBuddy(textBoxAge);
	formLayout->addRow(labelAge, textBoxAge);
	boxLayout->addWidget(details);


	main->show();
}

int GUI::runProgram() {
	return application.exec();
}
