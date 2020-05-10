//
// Created by Octavian Custura on 04/05/2020.
//

#include "Service.h"
#include "Surgery.h"
#include "NeonatalUnit.h"
#include <iostream>
#define NumberOfParameters 6
#define DepartmentType 1
Service::Service() {
	controller = Controller();
	file = "";
}

void Service::addDepartment(const std::string& parameters) {
	std::string arrayOfParameters[NumberOfParameters];
	int index = 0;
	for (auto character: parameters) {
		if (character == ',') {
			index++;
		}else {
			arrayOfParameters[index] += character;
		}
	}

	if (arrayOfParameters[DepartmentType].substr(1) == "Surgery") {
		controller.addDepartment(new Surgery(arrayOfParameters[0], std::stoi(arrayOfParameters[2].substr(1)), std::stoi(arrayOfParameters[3].substr(1))));
	}else  {
		controller.addDepartment(new NeonatalUnit(arrayOfParameters[0], std::stoi(arrayOfParameters[2]), std::stoi(arrayOfParameters[3]), std::stoi(arrayOfParameters[4]), std::stod(arrayOfParameters[5])));
	}
}

std::vector<HospitalDepartment *> Service::getAllDepartments() {
	return controller.getAllDepartments();
}

std::vector<HospitalDepartment *> Service::getAllEfficient() {
	return controller.getAllEfficientDepartments();
}

void Service::writeToFile() {
	controller.writeToFile(file);
}

void Service::setFile(const std::string& filename) {
	file = filename;
}
