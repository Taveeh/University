//
// Created by Octavian Custura on 20/03/2020.
//

#include "UI.h"
#include <iostream>
#include <map>
#include <utility>
typedef void (UI::*function)(std::string parameters);

UI::UI(Service& service) {
    this->service = service;
}

void UI::runProgramAdministrator() {
    std::map<std::string, function> mapOfChoices;
    mapOfChoices.insert(std::make_pair("add", &UI::addElement));
    mapOfChoices.insert(std::make_pair("delete", &UI::removeElement));
    mapOfChoices.insert(std::make_pair("update", &UI::updateElement));
    mapOfChoices.insert(std::make_pair("list", &UI::listAllElements));
    while(true) {
        std::string stringLine;
        std::getline(std::cin, stringLine);
        std::string command;
        bool isCommand = true;
        std::string parameters;
        for (char stringLineIndex : stringLine) {
            if (isCommand and stringLineIndex != ' ') {
                command += stringLineIndex;
            } else if (isCommand and stringLineIndex == ' ') {
                isCommand = false;
            }else if (!isCommand) {
                parameters += stringLineIndex;
            }
        }
        std::cout << "Command: " << command << " " << command.size() <<  "\nParameters: " << parameters << " " << parameters.size();
        if (command == "exit") {
            return;
        }
        if (mapOfChoices.find(command) == mapOfChoices.end()) {
           std::cout << "Invalid command";
        }else {
            mapOfChoices[command](parameters);
        }



    }
}
