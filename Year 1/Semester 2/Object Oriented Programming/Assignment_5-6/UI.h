//
// Created by Octavian Custura on 20/03/2020.
//

#ifndef ASSIGNMENT_5_6_UI_H
#define ASSIGNMENT_5_6_UI_H

#include "Service.h"

class UI {
private:
    Service service;
    void addElement(std::string commandParameters);

    void removeElement(std::string commandParameters);

    void updateElement(std::string commandParameters);

    void listAllElements(std::string commandParameters);


public:
    explicit UI(Service& service);
    void runProgramAdministrator();
};


#endif //ASSIGNMENT_5_6_UI_H
