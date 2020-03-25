//
// Created by Octavian Custura on 20/03/2020.
//

#include "UI.h"
#include <iostream>
#include <map>
#include <utility>
#include <functional>
//typedef void (UI::*function)(const std::string& parameters);
#define MAX_PARAMETERS 5
UI::UI(Service& service) {
    this->service = service;
}

void UI::runProgramAdministrator() {
    std::map<std::string, std::function<void(UI&, std::string)>> mapOfChoices;
    mapOfChoices["add"] = &UI::addElement;
    mapOfChoices["delete"] = &UI::removeElement;
    mapOfChoices["update"] = &UI::updateElement;
    mapOfChoices["list"] = &UI::listAllElements;
    while(true) {
        std::string stringLine;
        std::getline(std::cin, stringLine);
        std::string command;
        bool isCommand = true;
        std::string parameters;
        for (char stringLineIndex : stringLine) {
            if (isCommand and stringLineIndex != ' ') {
                command += stringLineIndex;
            } else if (isCommand) {
                isCommand = false;
            }else {
                parameters += stringLineIndex;
            }
        }
        if (command == "exit") {
            return;
        }
        auto currentChoice = mapOfChoices.find(command);
        if (currentChoice == mapOfChoices.end()) {
            std::cout << "Invalid command\n";
        }else {
            mapOfChoices[command](*this, parameters);
        }
    }
}

void UI::addElement(const std::string& commandParameters) {
    std::string ArrayOfParameters[MAX_PARAMETERS];
    int currentCommand = 0;
    for (auto commandParametersElement: commandParameters) {
        if (commandParametersElement != ',') {
            ArrayOfParameters[currentCommand] += commandParametersElement;
        }else {
            currentCommand++;
        }
    }
    try {
        service.addFootage(ArrayOfParameters[0], ArrayOfParameters[1], ArrayOfParameters[2], ArrayOfParameters[3], ArrayOfParameters[4]);
    }catch (std::exception& exception) {
        std::cout << "Invalid parameters\n";
    }
}

void UI::removeElement(const std::string &commandParameters) {
    try {
        service.deleteFootage(commandParameters);
    }catch (std::exception& exception){
        std::cout << "Invalid parameters\n";
    }
}

void UI::updateElement(const std::string &commandParameters) {
    std::string ArrayOfParameters[MAX_PARAMETERS];
    int currentCommand = 0;
    for (auto commandParametersElement: commandParameters) {
        if (commandParametersElement != ',') {
            ArrayOfParameters[currentCommand] += commandParametersElement;
        }else {
            currentCommand++;
        }
    }
    try {
        service.updateFootage(ArrayOfParameters[0], ArrayOfParameters[1], ArrayOfParameters[2], ArrayOfParameters[3], ArrayOfParameters[4]);
    }catch (std::exception& exception) {
        std::cout << "Invalid parameters\n";
    }
}

void UI::listAllElements(const std::string &commandParameters) {
    DynamicArray<Footage> arrayOfFootage = service.getAllElements();
    if (arrayOfFootage.getSize() == 0) {
        std::cout << "There are no footage in the list\n";
        return;
    }
    for (int arrayOfFootageIndex = 0; arrayOfFootageIndex < arrayOfFootage.getSize(); ++arrayOfFootageIndex) {
        std::cout << arrayOfFootage.getElement(arrayOfFootageIndex).toString() << "\n";
    }
}

void UI::runProgram() {
    std::string modeLine;
    std::getline(std::cin, modeLine);
    std::string command, mode;
    bool isCommand = true;
    for (auto modeLineIndex: modeLine) {
        if (isCommand and modeLineIndex != ' ') {
            command += modeLineIndex;
        }else if (isCommand) {
            isCommand = false;
        }else if (modeLineIndex != ' ') {
            mode += modeLineIndex;
        }
    }
    if (command != "mode") {
        std::cout << "Invalid command\n";
    }
    if (mode == "A") {
        runProgramAdministrator();
    }else {
        std::cout << "Invalid mode\n";
    }
}
