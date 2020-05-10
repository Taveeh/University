//
// Created by Octavian Custura on 04/05/2020.
//

#include "UI.h"
#include <iostream>
UI::UI() {
	service = Service();
}

void UI::runProgram() {
	while (true) {
		std::string command;
		std::getline(std::cin, command);
		if (command == "exit") {
			return;
		}
		std::string functionality, parameters;
		bool isCommand = true;
		for (auto character: command) {
			if (character == ' ' and isCommand) {
				isCommand = false;
			} else if (character != ' ' and isCommand) {
				functionality += character;
			} else {
				parameters += character;
			}
		}
		if (functionality == "add") {
			add(parameters);
		}else if (functionality == "list") {
			this->list(parameters);
		}else if (functionality == "fileLocation") {
			setFile(parameters);
		}
	}
}

void UI::add(const std::string& parameters) {
	service.addDepartment(parameters);
}

void UI::list(const std::string& parameters) {
	std::vector<HospitalDepartment*> arrayOfDepartments;
	if (parameters == "efficient") {
		arrayOfDepartments = service.getAllEfficient();
	} else {
		arrayOfDepartments = service.getAllDepartments();
	}
	if (service.file.empty()){
		for (auto department: arrayOfDepartments) {
			std::cout << department->toString() << std::endl;
		}
	}else {
		service.writeToFile();
	}

}

void UI::setFile(std::string parameters) {
	service.setFile(parameters);
}
