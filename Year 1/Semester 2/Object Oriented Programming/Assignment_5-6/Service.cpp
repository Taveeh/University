//
// Created by Octavian Custura on 19/03/2020.
//

#include "Service.h"
#include <exception>
#include <cassert>
#include <iostream>
Service::Service(Repository &newRepository) {
    repository = newRepository;
}

void Service::addFootage(const std::string &title, const std::string &type, const std::string &dateString,
                         const int &numberAccessed, const std::string &link) {
    std::exception invalidDateError = (const std::exception &) "Invalid date type";
    if (dateString.size() != 10) {
        throw std::exception(invalidDateError);
    }
    std::string dayString = dateString.substr(0, 2);
    std::string monthString = dateString.substr(3, 2);
    std::string yearString = dateString.substr(6, 4);

}

void testFoo() {
    auto repo = Repository();
    auto service = Service(repo);
    try {
        service.addFootage("dsaf", "fdsa", "123456", 123, "fadsafas");
        assert(false);
    }catch( std::exception& e){
        std::cout << e.what();
        assert(true);
    }
}