//
// Created by Octavian Custura on 20/04/2020.
//

#ifndef ASSIGNMENT_7_8_VALIDATOR_H
#define ASSIGNMENT_7_8_VALIDATOR_H

#include <vector>
#include <string>
#include <ctime>
#include "Exceptions.h"
#include "Footage.h"
#define SIZE_OF_DATE 10

class Validator {
private:
	std::vector<std::string> parametersToValidate;
	void validateAdd();
	void validateUpdate();
	static void validateRemove(){};
	/*
	 * Validates if the added date is valid
	 * Input:
	 *  day, month, year - int
	 * Output:
	 *
	 */
	static bool validateNewDate(int day, int month, int year);
public:
	explicit Validator(const std::vector<std::string>&  parametersToValidate);
};


#endif //ASSIGNMENT_7_8_VALIDATOR_H
