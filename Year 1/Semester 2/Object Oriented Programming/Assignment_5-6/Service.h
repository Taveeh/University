//
// Created by Octavian Custura on 19/03/2020.
//

#ifndef ASSIGNMENT_5_6_SERVICE_H
#define ASSIGNMENT_5_6_SERVICE_H

#include <string>
#include "Repository.h"
#define SIZE_OF_DATE 10
class Service {
private:
    Repository repository;
    static bool validateNewDate(int day, int month, int year);
public:
    Service();
    explicit Service(Repository& newRepository);
    void addFootage(const std::string &title, const std::string &type, const std::string &dateString, const std::string &numberAccessedString, const std::string &link);
    void deleteFootage(const std::string& title);
    void updateFootage(const std::string &title, const std::string &type, const std::string &dateString, const std::string &numberAccessedString, const std::string &link);
    DynamicArray<Footage> getAllElements();
};

#endif //ASSIGNMENT_5_6_SERVICE_H
