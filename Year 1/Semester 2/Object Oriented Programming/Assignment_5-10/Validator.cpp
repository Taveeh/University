//
// Created by Octavian Custura on 20/04/2020.
//

#include "Validator.h"

#include <iostream>
#include <sstream>

Validator::Validator(const std::vector<std::string>&  parametersToValidate1): parametersToValidate(parametersToValidate1) {
	if (parametersToValidate1.empty()) {
		throw ValidationException("Invalid parameters");
	}
	if (parametersToValidate1[0] == "add") {
		validateAdd();
	}else if (parametersToValidate1[0] == "remove") {
		validateRemove();
	}else if (parametersToValidate1[0] == "update") {
		validateUpdate();
	}else {
		throw ValidationException("Invalid operation to validate");
	}
}

void Validator::validateAdd() {
	if ((parametersToValidate.begin() + 3)->size() != SIZE_OF_DATE + 1) {
		throw ValidationException("Invalid date format");
	}
	std::string newType = (parametersToValidate.begin() + 2)->substr(1, (parametersToValidate.begin() + 2)->size() - 1);
	std::string newNumberAccessedString =  (parametersToValidate.begin() + 4)->substr(1,  (parametersToValidate.begin() + 4)->size() - 1);
	std::string monthString = (parametersToValidate.begin() + 3)->substr(1, 2);
	std::string dayString = (parametersToValidate.begin() + 3)->substr(4, 2);
	std::string yearString = (parametersToValidate.begin() + 3)->substr(7, 4);
	std::stringstream convertDayStringToInt(dayString);
	std::stringstream convertMonthStringToInt(monthString);
	std::stringstream convertYearStringToInt(yearString);
	int newDay = 0, newMonth = 0, newYear = 0;
	convertDayStringToInt >> newDay;
	convertMonthStringToInt >> newMonth;
	convertYearStringToInt >> newYear;
	time_t currentTime = time(nullptr);
	tm* currentTimePointer = localtime(&currentTime);
	if (!validateNewDate(newDay, newMonth, newYear)) {
		throw ValidationException("Invalid date");
	}
	Date currentDate = Date(currentTimePointer->tm_mday, currentTimePointer->tm_mon + 1, currentTimePointer->tm_year + 1900);
	auto newDate = Date(newDay, newMonth, newYear);
	if (currentDate < newDate) {
		throw ValidationException("Date too much in the future");
	}
	std::stringstream convertNumberAccessedStringToInt(newNumberAccessedString);
	int numberAccessed = 0;
	convertNumberAccessedStringToInt >> numberAccessed;
	if (numberAccessed < 0) {
		throw ValidationException("Invalid access count");
	}

}


bool Validator::validateNewDate(int day, int month, int year) {
	if (day > 31 or month > 12) {
		return false;
	}
#define JUNE 6
#define APRIL 4
#define SEPTEMBER 9
#define NOVEMBER 11
	if (month == JUNE or month == APRIL or month == SEPTEMBER or month == NOVEMBER)
		if (day > 30) return false;
#define FEBRUARY 2
# define isLeapYear(year) (((year) % 4 == 0 and (year) % 100 != 0) or (year) % 400 == 0)
	if (month == FEBRUARY) {
		if (isLeapYear(year)) {
			if (day > 29) return false;
		} else if (day > 28)
			return false;
	}
	return year >= 1800;
}


void Validator::validateUpdate() {
	if ((parametersToValidate.begin() + 3)->size() != SIZE_OF_DATE + 1) {
		throw ValidationException("Invalid date format");
	}
	std::string newType = (parametersToValidate.begin() + 2)->substr(1, (parametersToValidate.begin() + 2)->size() - 1);
	std::string newNumberAccessedString =  (parametersToValidate.begin() + 4)->substr(1,  (parametersToValidate.begin() + 4)->size() - 1);
	std::string monthString = (parametersToValidate.begin() + 3)->substr(1, 2);
	std::string dayString = (parametersToValidate.begin() + 3)->substr(4, 2);
	std::string yearString = (parametersToValidate.begin() + 3)->substr(7, 4);
	std::stringstream convertDayStringToInt(dayString);
	std::stringstream convertMonthStringToInt(monthString);
	std::stringstream convertYearStringToInt(yearString);
	int newDay = 0, newMonth = 0, newYear = 0;
	convertDayStringToInt >> newDay;
	convertMonthStringToInt >> newMonth;
	convertYearStringToInt >> newYear;
	time_t currentTime = time(nullptr);
	tm* currentTimePointer = localtime(&currentTime);
	if (!validateNewDate(newDay, newMonth, newYear)) {
		throw ValidationException("Invalid date");
	}
	Date currentDate = Date(currentTimePointer->tm_mday, currentTimePointer->tm_mon + 1, currentTimePointer->tm_year + 1900);
	auto newDate = Date(newDay, newMonth, newYear);
	if (currentDate < newDate) {
		throw ValidationException("Date too much in the future");
	}
	std::stringstream convertNumberAccessedStringToInt(newNumberAccessedString);
	int numberAccessed = 0;
	convertNumberAccessedStringToInt >> numberAccessed;
	if (numberAccessed < 0) {
		throw ValidationException("Invalid access count");
	}
}
