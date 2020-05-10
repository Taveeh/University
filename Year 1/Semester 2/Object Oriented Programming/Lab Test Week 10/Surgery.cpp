//
// Created by Octavian Custura on 04/05/2020.
//

#include "Surgery.h"

Surgery::Surgery(const std::string &newHospitalName, int newNumberOfDoctors, int newNumberOfPatients) {
	hospitalName = newHospitalName;
	numberOfDoctors = newNumberOfDoctors;
	numberOfPatients = newNumberOfPatients;
}

bool Surgery::isEfficient() {
	return (numberOfPatients/ numberOfDoctors >= 2);
}

std::string Surgery::toString() {
	std::string efficientString;
	if (isEfficient()) {
		efficientString = "efficient";
	}else {
		efficientString = "not efficient";
	}
	return hospitalName + " Surgery " + std::to_string(numberOfDoctors) + " " + std::to_string(numberOfPatients) + " " + efficientString;
}
