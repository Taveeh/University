//
// Created by Octavian Custura on 18/03/2020.
//

#include "Footage.h"

#include <utility>

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
    if (compareDate1.getYear() < compareDate2.getYear())
        return true;
    if (compareDate1.getYear() > compareDate2.getYear())
        return false;
    if (compareDate1.getMonth() < compareDate1.getMonth())
        return true;
    if (compareDate1.getMonth() > compareDate2.getMonth())
        return false;
    return compareDate1.getDay() <= compareDate1.getDay();
}

Date::Date() {
    day = 0;
    year = 0;
    month = 0;
}

std::string Date::toString() const {
    std::string stringDate;
    stringDate += std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);
    return stringDate;
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
