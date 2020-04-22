//
// Created by Octavian Custura on 20/03/2020.
//

#ifndef ASSIGNMENT_5_6_UI_H
#define ASSIGNMENT_5_6_UI_H

#include "Service.h"

class UI {
private:
	Service service;
	void addElement(const std::string& commandParameters);

	void removeElement(const std::string& commandParameters);

	void updateElement(const std::string& commandParameters);

	void listAllElements(const std::string& commandParameters);

	void runProgramAdministrator();

	void changeMode(const std::string& commandParameters);

	void runProgramFieldAgent();

	void nextElement(const std::string& commandParameters);

	void saveTitle(const std::string& commandParameters);

	void listProperty(const std::string& commandParameters);

	void myList(const std::string& commandParameters);

	void openMyList(const std::string& commandParameters);

public:
	explicit UI(Service& service);

	void runProgram();

};


#endif //ASSIGNMENT_5_6_UI_H
