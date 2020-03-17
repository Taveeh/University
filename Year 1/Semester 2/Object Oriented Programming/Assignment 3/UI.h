//
// Created by Octavian Custura on 06/03/2020.
//

#pragma once

#include "service.h"

typedef struct {
    Service* service;
}UI;

void parseReading(char* stringToBeParsed, char**parsedArrayOfStrings);

void readUserCommand(UI* ui);

UI* createUI(Service* service);

void destroyUI(UI* ui);

void addMapUI(UI* ui, char** parsedArrayOdStrings);

void updateMapUI(UI* ui, char** parsedArrayOfStrings);

void listAllMapsUI(UI* ui, char** parsedArrayOfStrings);

void listAllMapsUIByType(UI* ui, char** parsedArrayOfStrings);

void removeMapUI(UI* ui, char** parsedArrayOfStrings);

void sortByAgeUI(UI* ui, char** parsedArrayOfStrings);

void undoOperationUI(UI* ui);

void redoOperationUI(UI* ui);