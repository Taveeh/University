//
// Created by Octavian Custura on 18/03/2020.
//

#include "Footage.h"
#include <sstream>

#define MAX_PARAMETERS_FOOTAGE 5
#define TITLE 0
#define TYPE 1
#define DATE 2
#define ACCESS_COUNT 3
#define LINK 4
Date::Date(int day, int month, int year):day{day}, month{month}, year{year} {

}

int Date::getDay() const {
	return day;
}

int Date::getMonth() const {
	return month;
}

int Date::getYear() const {
	return year;
}

bool operator<(const Date &compareDate1, const Date &compareDate2) {
	if (compareDate1.getYear() < compareDate2.getYear()) return true;
	if (compareDate1.getYear() > compareDate2.getYear()) return false;
	if (compareDate1.getMonth() < compareDate1.getMonth()) return true;
	if (compareDate1.getMonth() > compareDate2.getMonth()) return false;
	return compareDate1.getDay() <= compareDate1.getDay();
}

Date::Date() {
	day = 0;
	year = 0;
	month = 0;
}

std::string Date::toString() const {
	std::string stringDate;
	if (month / 10 == 0) stringDate += '0';
	stringDate += std::to_string(month) + "-";
	if (day / 10 == 0) stringDate += '0';
	stringDate += std::to_string(day) + "-" + std::to_string(year);
	return stringDate;
}

std::istream &operator>>(std::istream &inputStream, Date &date) {
	std::string dateString;
	inputStream >> dateString;
	std::string monthString = dateString.substr(0, 2);
	std::string dayString = dateString.substr(3, 2);
	std::string yearString = dateString.substr(6, 4);
	std::stringstream convertDayStringToInt(dayString);
	std::stringstream convertMonthStringToInt(monthString);
	std::stringstream convertYearStringToInt(yearString);
	int newDay = 0, newMonth = 0, newYear = 0;
	convertDayStringToInt >> newDay;
	convertMonthStringToInt >> newMonth;
	convertYearStringToInt >> newYear;
	date = Date(newDay, newMonth, newYear);
	return inputStream;
}

std::ostream &operator<<(std::ostream &outputStream, const Date &date) {
	if (date.month / 10 == 0) {
		outputStream << 0;
	}
	outputStream << date.month << '-';
	if (date.day / 10 == 0) {
		outputStream << 0;
	}
	outputStream << date.day << '-' << date.year;
	return outputStream;
}


Footage::Footage(std::string title, std::string type, Date date, int numberAccessed, std::string link):title{std::move(title)}, type{std::move(type)}, date{date}, numberAccessed{numberAccessed}, link{std::move(link)} {

}

void Footage::changeType(std::string newType) {
	type = std::move(newType);
}

void Footage::changeDate(Date newDate) {
	date = newDate;
}

void Footage::changeAccessCount(int newAccessCount) {
	numberAccessed = newAccessCount;
}

void Footage::changeLink(std::string newLink) {
	link = std::move(newLink);
}

std::string Footage::getTitle() const {
	return title;
}

std::string Footage::getType() const {
	return type;
}

Date Footage::getDate() const {
	return date;
}

int Footage::getAccessCount() const {
	return numberAccessed;
}

std::string Footage::getLink() const {
	return link;
}

Footage::Footage() {
	title = "";
	type = "";
	date = Date();
	numberAccessed = 0;
	link = "";
}

std::string Footage::toString() const {
	std::string stringFootage;
	stringFootage += "Title: " + title + " Type: " + type + " Date: " + date.toString() + " Access count: " + std::to_string(numberAccessed) + " Link: " + link;
	return stringFootage;
}

std::istream &operator>>(std::istream &inputStream, Footage &footage) {
	std::string footageLine;
	getline(inputStream, footageLine);
	if (footageLine.empty()) {
		footage = Footage();
	}else {
		std::string ArrayOfParameters[MAX_PARAMETERS_FOOTAGE];
		int currentCommand = 0;
		for (auto commandParametersElement: footageLine) {
			if (commandParametersElement != ',') {
				ArrayOfParameters[currentCommand] += commandParametersElement;
			} else {
				currentCommand++;
			}
		}
		std::stringstream dateStream(ArrayOfParameters[DATE]);
		Date newDate;
		dateStream >> newDate;
		std::string newTitle = ArrayOfParameters[TITLE], newType = ArrayOfParameters[TYPE];
		std::string newLink = ArrayOfParameters[LINK];
		std::stringstream accessCountStream(ArrayOfParameters[ACCESS_COUNT]);
		int accessCount = 0;
		accessCountStream >> accessCount;
		footage = Footage(newTitle, newType, newDate, accessCount, newLink);
	}
	return inputStream;
}

std::ostream &operator<<(std::ostream &outputStream, const Footage &footage) {
	outputStream << footage.title <<',' << footage.type << ',' << footage.date << ',' << footage.numberAccessed << ',' << footage.link << std::endl;
	return outputStream;
}