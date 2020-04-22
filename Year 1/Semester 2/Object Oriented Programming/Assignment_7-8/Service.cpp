//
// Created by Octavian Custura on 19/03/2020.
//

#include "Service.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

Service::Service() {
	repository = nullptr;
	myListRepository = nullptr;
}

void Service::addFootage(const std::string &title, const std::string &type,const std::string &dateString, const std::string &numberAccessedString, const std::string &link) {
	std::vector<std::string> arrayOfParameters;
	arrayOfParameters.push_back("add");
	arrayOfParameters.push_back(title);
	arrayOfParameters.push_back(type);
	arrayOfParameters.push_back(dateString);
	arrayOfParameters.push_back(numberAccessedString);
	arrayOfParameters.push_back(link);
	try {
		auto validator = Validator(arrayOfParameters);
	}catch (ValidationException& exception) {
		throw ValidationException(exception.what());
	}
	const std::string& newTitle = title;
	std::string newType = type.substr(1, type.size() - 1);
	std::string newNumberAccessedString = numberAccessedString.substr(1, numberAccessedString.size() - 1);
	std::string monthString = dateString.substr(1, 2);
	std::string dayString = dateString.substr(4, 2);
	std::string yearString = dateString.substr(7, 4);
	std::stringstream convertDayStringToInt(dayString);
	std::stringstream convertMonthStringToInt(monthString);
	std::stringstream convertYearStringToInt(yearString);
	int newDay = 0, newMonth = 0, newYear = 0;
	convertDayStringToInt >> newDay;
	convertMonthStringToInt >> newMonth;
	convertYearStringToInt >> newYear;
	auto newDate = Date(newDay, newMonth, newYear);
	std::stringstream convertNumberAccessedStringToInt(newNumberAccessedString);
	int numberAccessed = 0;
	convertNumberAccessedStringToInt >> numberAccessed;
	auto newFootage = Footage(newTitle, newType, newDate, numberAccessed, link.substr(1));
	try {
		repository->addFootage(newFootage);
	}catch (RepositoryException& exception) {
		throw ValidationException("Duplicate footage");
	}
}

void Service::deleteFootage(const std::string& title) {
	try {
		repository->deleteFootage(title);
//		myListRepository->deleteFootage(title);
	}catch (RepositoryException& e) {
		throw e;
	}
}

void Service::updateFootage(const std::string &title, const std::string &type, const std::string &dateString,
                            const std::string &numberAccessedString, const std::string &link) {
	std::vector<std::string> arrayOfParameters;
	arrayOfParameters.push_back("update");
	arrayOfParameters.push_back(title);
	arrayOfParameters.push_back(type);
	arrayOfParameters.push_back(dateString);
	arrayOfParameters.push_back(numberAccessedString);
	arrayOfParameters.push_back(link);
	try {
		auto validator = Validator(arrayOfParameters);
	}catch (ValidationException& exception) {
		throw exception;
	}
	const std::string& newTitle = title;
	std::string newType = type.substr(1, type.size() - 1);
	std::string newNumberAccessedString = numberAccessedString.substr(1, numberAccessedString.size() - 1);
	std::string monthString = dateString.substr(1, 2);
	std::string dayString = dateString.substr(4, 2);
	std::string yearString = dateString.substr(7, 4);
	std::stringstream convertDayStringToInt(dayString);
	std::stringstream convertMonthStringToInt(monthString);
	std::stringstream convertYearStringToInt(yearString);
	int newDay = 0, newMonth = 0, newYear = 0;
	convertDayStringToInt >> newDay;
	convertMonthStringToInt >> newMonth;
	convertYearStringToInt >> newYear;
	auto newDate = Date(newDay, newMonth, newYear);
	std::stringstream convertNumberAccessedStringToInt(newNumberAccessedString);
	int numberAccessed = 0;
	convertNumberAccessedStringToInt >> numberAccessed;
	auto newFootage = Footage(newTitle, newType, newDate, numberAccessed, link.substr(1));
	try {
		repository->updateFootage(newFootage);
//		myListRepository->updateFootage(newFootage);
	}catch (RepositoryException & exception) {
		throw exception;
	}
}

std::vector<Footage> Service::getAllElements() {
	return repository->getAllFootage();
}

//Service::Service(): repository(FileRepository(std::to_string(0))) {
//
//}

Footage Service::getCurrent() {
	return repository->getCurrentElement();
}

void Service::addToMyList(const std::string &title) {
	auto arrayOfTapes = repository->getAllFootage();
	for (auto & arrayOfTape : arrayOfTapes) {
		if (arrayOfTape.getTitle() == title) {
			myListRepository->addFootage(arrayOfTape);
			return;
		}
	}
	throw ValidationException("Element does not exist");
}

std::vector<Footage> Service::getMyList() {
	return myListRepository->getAllFootage();
}

std::vector<Footage> Service::getFilteredList(const std::string &type, const std::string &maximumAccessCount) {
	auto arrayOfTapes = repository->getAllFootage();
	std::string newNumberAccessedString = maximumAccessCount.substr(1, maximumAccessCount.size() - 1);
	std::stringstream convertNumberAccessedStringToInt(newNumberAccessedString);
	int numberAccessed = 0;
	convertNumberAccessedStringToInt >> numberAccessed;
	if (numberAccessed < 0) {
		throw ValidationException("Invalid access count");
	}
	std::vector<Footage> filteredList;
	std::copy_if(arrayOfTapes.begin(), arrayOfTapes.end(), std::back_inserter(filteredList), [numberAccessed, &type](const Footage& footage) {
		return footage.getAccessCount() < numberAccessed and footage.getType() == type;
	});
	return filteredList;
}

void Service::setPath(const std::string& fileName, const std::string& repositoryName) {
	if (repositoryName == "mylist") {
		if (fileName.substr(fileName.size() - 3) == "csv") {
			myListRepository = new FileRepository(fileName);
		}else if (fileName.substr(fileName.size() - 4) == "html") {
			myListRepository = new HtmlFileRepository(fileName);
		}else {
			throw ValidationException("Invalid format");
		}
	}else {
		if (fileName.substr(fileName.size() - 3) == "txt") {
			repository = new FileRepository(fileName);
		}else {
			repository = new SQLRepository(fileName);
		}
	}
}

Service::~Service() {
	delete repository;
	delete myListRepository;
}

void Service::openMyList() {
	myListRepository->openList();
}


