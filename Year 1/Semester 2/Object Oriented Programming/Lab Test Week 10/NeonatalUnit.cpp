//
// Created by Octavian Custura on 04/05/2020.
//

#include "NeonatalUnit.h"

bool NeonatalUnit::isEfficient() {
	return averageGrade > 8.5 and numberOfNewborns > numberOfMothers;
}

std::string NeonatalUnit::toString() {
	return hospitalName + " Neonatal Unit " + std::to_string(numberOfDoctors) + " " + std::to_string(numberOfMothers) + " " + std::to_string(numberOfNewborns) + " " + std::to_string(averageGrade);
}

NeonatalUnit::NeonatalUnit(const std::string &newHospitalName, int newNumberOfDoctors, int newNumberOfNewborns,
                           int newNumberOfMothers, double newAverageGrade) {
	hospitalName = newHospitalName;
	numberOfDoctors = newNumberOfDoctors;
	numberOfNewborns = newNumberOfNewborns;
	numberOfMothers = newNumberOfMothers;
	averageGrade = newAverageGrade;
}
