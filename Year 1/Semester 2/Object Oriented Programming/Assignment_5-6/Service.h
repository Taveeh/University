//
// Created by Octavian Custura on 19/03/2020.
//

#ifndef ASSIGNMENT_5_6_SERVICE_H
#define ASSIGNMENT_5_6_SERVICE_H

#include <string>
#include "Repository.h"

class Service {
private:
    Repository repository;
public:
    explicit Service(Repository& newRepository);
    void addFootage(const std::string& title, const std::string& type, const std::string& dateString,const int& numberAccessed, const std::string& link);
    void deleteFootage(std::string title);
    void updateFootage(const std::string& title, const std::string& type, const std::string& dateString,const int& numberAccessed, const std::string& link);

};
void testFoo();

#endif //ASSIGNMENT_5_6_SERVICE_H
