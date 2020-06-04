//
// Created by Octavian Custura on 19/03/2020.
//

#include "Service.h"
#include <iostream>
#include <sstream>
#include <map>

Service::Service() {
	repository = nullptr;
	myListRepository = nullptr;
	undoRedoIndex = 0;
	undoRedoList = std::vector<Action*>();
	undoRedoMyList = std::vector<Action*>();
	undoRedoMyListIndex = 0;
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
	undoRedoList.resize(undoRedoIndex);
	undoRedoList.push_back(new ActionAdd(newFootage, repository));
	undoRedoIndex++;
}

void Service::deleteFootage(const std::string& title) {
	Footage removedFootage;
	try {
		for (const auto& footage: repository->getAllFootage()) {
			if (footage.getTitle() == title) {
				removedFootage = footage;
			}
		}
		repository->deleteFootage(title);
//		myListRepository->deleteFootage(title);
	}catch (RepositoryException& e) {
		throw e;
	}
	if (myListRepository != nullptr) {
		for (const auto& footage: myListRepository->getAllFootage()) {
			if (footage.getTitle() == title) {
				myListRepository->deleteFootage(title);
				break;
			}
		}
	}
	undoRedoList.resize(undoRedoIndex);
	undoRedoList.push_back(new ActionRemove(removedFootage, repository));
	undoRedoIndex++;
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
	Footage oldFootage;
	try {
		for (auto footage: repository->getAllFootage()) {
			if (footage.getTitle() == title) {
				oldFootage = footage;
			}
		}
		repository->updateFootage(newFootage);
//		myListRepository->updateFootage(newFootage);
	}catch (RepositoryException & exception) {
		throw exception;
	}
	if (myListRepository != nullptr) {
		for (const auto& footage: myListRepository->getAllFootage()) {
			if (footage.getTitle() == title) {
				myListRepository->updateFootage(newFootage);
				break;
			}
		}
	}
	undoRedoList.resize(undoRedoIndex);
	undoRedoList.push_back(new ActionUpdate(oldFootage, newFootage, this->repository));
	undoRedoIndex++;
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
			undoRedoMyList.resize(undoRedoMyListIndex);
			undoRedoMyList.push_back(new ActionAdd(arrayOfTape, myListRepository));
			undoRedoMyListIndex++;
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
		if (fileName == "memory"){
			myListRepository = new MemoryRepository();
		}else if (fileName.substr(fileName.size() - 3) == "csv") {
			myListRepository = new FileRepository(fileName);
		}else if (fileName.substr(fileName.size() - 4) == "html") {
			myListRepository = new HtmlFileRepository(fileName);
		}else {
			throw ValidationException("Invalid format");
		}
	}else if (repositoryName == "repository"){
		if (fileName == "memory"){
			repository = new MemoryRepository();
		}else if (fileName.substr(fileName.size() - 3) == "txt") {
			repository = new FileRepository(fileName);
		}else if (fileName.substr(fileName.size() - 7) == "sqlite3") {
			repository = new SQLRepository(fileName);
		}else if (fileName.substr(fileName.size() - 4) == "html") {
			repository = new HtmlFileRepository(fileName);
		}else {
			throw ValidationException("Invalid format");
		}
	}
}

Service::~Service() {
	delete repository;
	delete myListRepository;
	for (auto action: undoRedoList) {
		delete action;
	}
	for (auto action: undoRedoMyList) {
		delete action;
	}
}

void Service::openMyList() {
	myListRepository->openList();
}

void Service::undo(bool storage) {
	if (storage) {
		if (undoRedoIndex == 0) {
			throw std::runtime_error("No more undos");
		}
		undoRedoList[--undoRedoIndex]->executeUndo();
	}else {
		if (undoRedoMyListIndex == 0) {
			throw std::runtime_error("No more undos");
		}
		undoRedoMyList[--undoRedoMyListIndex]->executeUndo();
	}
}

void Service::redo(bool storage) {
	if (storage) {
		if (undoRedoIndex == undoRedoList.size()) {
			throw std::runtime_error("No more redos");
		}
		undoRedoList[undoRedoIndex++]->executeRedo();
	}else {
		if (undoRedoMyListIndex == undoRedoMyList.size()) {
			throw std::runtime_error("No more undos");
		}
		undoRedoMyList[undoRedoMyListIndex++]->executeRedo();
	}
}

void Service::editMyList(const std::string& title, int field, const std::string& value) {
	Footage oldFootage;
	for (const auto& footage: repository->getAllFootage()) {
		if (footage.getTitle() == title) {
			oldFootage = footage;
		}
	}
	Footage newFootage = oldFootage;
	switch (field) {
		case 1:
			newFootage.changeType(value);
			break;
		case 2: {
			std::stringstream stringToDate(value);
			Date newDate;
			stringToDate >> newDate;
			newFootage.changeDate(newDate);
			break;
		}
		case 3:
			newFootage.changeAccessCount(std::stoi(value));
			break;
		case 4:
			newFootage.changeLink(value);
			break;
		default:
			break;
	}
	myListRepository->updateFootage(newFootage);
	undoRedoMyList.resize(undoRedoMyListIndex);
	undoRedoMyList.push_back(new ActionUpdate(oldFootage, newFootage, myListRepository));
	undoRedoMyListIndex++;
}



