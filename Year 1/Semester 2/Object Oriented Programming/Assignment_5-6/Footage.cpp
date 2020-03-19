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

bool operator<=(const Date &compareDate1, const Date &compareDate2) {
    if (compareDate1.getYear() < compareDate2.getYear()) return true;
    if (compareDate1.getYear() > compareDate2.getYear()) return false;
    if (compareDate1.getMonth() < compareDate1.getMonth()) return true;
    if (compareDate1.getMonth() > compareDate1.getMonth()) return false;
    return compareDate1.getDay() <= compareDate1.getDay();
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

std::string Footage::getTitle() const{
    return title;
}

std::string Footage::getType() {
    return type;
}

Date Footage::getDate() {
    return date;
}

int Footage::getAccessCount() {
    return numberAccessed;
}

std::string Footage::getLink() {
    return link;
}
