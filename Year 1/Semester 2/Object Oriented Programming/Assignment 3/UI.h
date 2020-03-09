//
// Created by Octavian Custura on 06/03/2020.
//

#pragma once

#include "service.h"

typedef struct {
    Service* service;
}UI;

void parseReading(char* stringToBeParsed, char parsedArrayOfStrings[5][50]);

void readUserCommand(UI* ui);

UI createUI(Service* service);