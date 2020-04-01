//
// Created by Octavian Custura on 19/03/2020.
//

#include "Service.h"
#include <exception>
//#include <cassert>
#include <iostream>
#include <sstream>
#include <ctime>

Service::Service(Repository &newRepository) {
    repository = newRepository;
    myListRepository = Repository();
}

void Service::addFootage(const std::string &title, const std::string &type,const std::string &dateString, const std::string &numberAccessedString, const std::string &link) {
    if (dateString.size() != SIZE_OF_DATE + 1) {
        throw std::exception();
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
    int newDay, newMonth, newYear;
    convertDayStringToInt >> newDay;
    convertMonthStringToInt >> newMonth;
    convertYearStringToInt >> newYear;
    time_t currentTime = time(nullptr);
    tm* currentTimePointer = localtime(&currentTime);
    if (!validateNewDate(newDay, newMonth, newYear)) {
        throw std::exception();
    }
    Date currentDate = Date(currentTimePointer->tm_mday, currentTimePointer->tm_mon + 1, currentTimePointer->tm_year + 1900);
    auto newDate = Date(newDay, newMonth, newYear);
    if (currentDate < newDate) {
        throw std::exception();
    }
    std::stringstream convertNumberAccessedStringToInt(newNumberAccessedString);
    int numberAccessed;
    convertNumberAccessedStringToInt >> numberAccessed;
    if (numberAccessed < 0) {
        throw std::exception();
    }
    auto newFootage = Footage(newTitle, newType, newDate, numberAccessed, link);
    try {
        repository.addFootage(newFootage);
    }catch (std::exception& exception) {
        throw std::exception();
    }
}

bool Service::validateNewDate(int day, int month, int year) {
    if (day > 31 or month > 12) {
        return false;
    }
#define JULY 6
#define APRIL 4
#define SEPTEMBER 9
#define NOVEMBER 11
    if (month == JULY or month == APRIL or month == SEPTEMBER or month == NOVEMBER) {
        if (day > 30) {
            return false;
        }
    }
#define FEBRUARY 2
# define isLeapYear(year) (year % 4 == 0 and year % 100 != 0) or year % 400 == 0
    if (month == FEBRUARY) {
        if (isLeapYear(year)) {
            if (day > 29) {
                return false;
            }
        } else if (day > 28)
            return false;
    }
    return year >= 1800;
}

void Service::deleteFootage(const std::string& title) {
    try {
        repository.deleteFootage(title);
    }catch (std::exception& e) {
        throw std::exception();
    }
}

void Service::updateFootage(const std::string &title, const std::string &type, const std::string &dateString,
                            const std::string &numberAccessedString, const std::string &link) {
    if (dateString.size() != SIZE_OF_DATE + 1) {
        throw std::exception();
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
    int newDay, newMonth, newYear;
    convertDayStringToInt >> newDay;
    convertMonthStringToInt >> newMonth;
    convertYearStringToInt >> newYear;
    time_t currentTime = time(nullptr);
    tm* currentTimePointer = localtime(&currentTime);
    if (!validateNewDate(newDay, newMonth, newYear)) {
        throw std::exception();
    }
    Date currentDate = Date(currentTimePointer->tm_mday, currentTimePointer->tm_mon + 1, currentTimePointer->tm_year + 1900);
    auto newDate = Date(newDay, newMonth, newYear);
    if (currentDate < newDate) {
        throw std::exception();
    }
    std::stringstream convertNumberAccessedStringToInt(newNumberAccessedString);
    int numberAccessed;
    convertNumberAccessedStringToInt >> numberAccessed;
    if (numberAccessed < 0) {
        throw std::exception();
    }
    auto newFootage = Footage(newTitle, newType, newDate, numberAccessed, link);
    try {
        repository.updateFootage(newFootage);
    }catch (std::exception & exception) {
        throw exception;
    }
}

DynamicArray<Footage> Service::getAllElements() {
    return repository.getAllFootage();
}

Service::Service() {
    this->repository = Repository();
}

Footage Service::getCurrent() {
    return repository.getCurrentElement();
}

void Service::addToMyList(const std::string &title) {
    auto arrayOfTapes = repository.getAllFootage();
    for (int indexFootage = 0; indexFootage < arrayOfTapes.getSize(); ++indexFootage) {
        if (arrayOfTapes.getElement(indexFootage).getTitle() == title) {
            myListRepository.addFootage(arrayOfTapes.getElement(indexFootage));
            return;
        }
    }
    throw std::exception();
}

DynamicArray<Footage> Service::getMyList() {
    return myListRepository.getAllFootage();
}

DynamicArray<Footage> Service::getFilteredList(const std::string &type, const std::string &maximumAccessCount) {
    auto arrayOfTapes = repository.getAllFootage();
    std::string newNumberAccessedString = maximumAccessCount.substr(1, maximumAccessCount.size() - 1);
    std::stringstream convertNumberAccessedStringToInt(newNumberAccessedString);
    int numberAccessed;
    convertNumberAccessedStringToInt >> numberAccessed;
    if (numberAccessed < 0) {
        throw std::exception();
    }
    DynamicArray<Footage> filteredList = DynamicArray<Footage>();
    for (int i = 0; i < arrayOfTapes.getSize(); ++i) {
        if (arrayOfTapes.getElement(i).getType() == type and arrayOfTapes.getElement(i).getAccessCount() < numberAccessed) {
            filteredList.addElement(arrayOfTapes.getElement(i));
        }
    }
    return filteredList;
}


