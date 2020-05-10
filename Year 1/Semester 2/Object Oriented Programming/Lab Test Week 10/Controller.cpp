//
// Created by Octavian Custura on 04/05/2020.
//

#include "Controller.h"
#include <fstream>
void Controller::addDepartment(HospitalDepartment* newHospitalDepartment) {
	arrayOfHospitalDepartments.push_back(newHospitalDepartment);
}

std::vector<HospitalDepartment *> Controller::getAllDepartments() {
	return arrayOfHospitalDepartments;
}

std::vector<HospitalDepartment *> Controller::getAllEfficientDepartments() {
	std::vector<HospitalDepartment*> efficientHospitalDepartments;
	for (auto department: arrayOfHospitalDepartments) {
		if (department->isEfficient()) {
			efficientHospitalDepartments.push_back(department);
		}
	}
	return efficientHospitalDepartments;
}

void Controller::writeToFile(const std::string &filename) {
	std::ofstream fileOut(filename);
	for (auto department: arrayOfHospitalDepartments) {
		fileOut << department->toString() << std::endl;
	}
}

Controller::Controller() = default;
