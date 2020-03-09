//
// Created by Octavian Custura on 06/03/2020.
//

#include "UI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void parseReading(char* stringToBeParsed, char parsedArrayOfStrings[5][50]) {
    char *p;
    p = strtok(stringToBeParsed, " ");
    int indexWordFromCommands = 0;
    while (p != NULL) {
        strcpy(parsedArrayOfStrings[indexWordFromCommands++], p);
        p = strtok(NULL, " ");
    }
    if (strcmp(parsedArrayOfStrings[0], "add") == 0 || strcmp(parsedArrayOfStrings[0], "update") == 0) {
        for (int wordInParsedString = 1; wordInParsedString < 4; ++wordInParsedString) {
            parsedArrayOfStrings[wordInParsedString][strlen(
                    parsedArrayOfStrings[wordInParsedString]) - 1] = '\0';
        }

    }
}

void readUserCommand(UI *ui) {
    char userCommand[256];
    while(1) {
        scanf("%[^\n]%*c", userCommand);
        char commandAndParameters[5][50];
        for (int i = 0; i < 5; ++i) {
            commandAndParameters[i][0] = '\0';
        }
        parseReading(userCommand, commandAndParameters);
        if (strcmp(commandAndParameters[0], "exit") == 0) {
            return;
        }
        if (strcmp(commandAndParameters[0], "add") == 0) {
            int mapCatalogueNumber = atoi(commandAndParameters[1]);
            char stateOfDeterioration[50], mapType[50];
            int yearsOfStorage = atoi(commandAndParameters[4]);
            strcpy(stateOfDeterioration, commandAndParameters[2]);
            strcpy(mapType, commandAndParameters[3]);
            if (addMapService(ui->service, mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage) == 0) {
                printf("No!\n");
            }
        } else if (strcmp(commandAndParameters[0], "update") == 0) {
            int mapCatalogueNumber = atoi(commandAndParameters[1]);
            char stateOfDeterioration[50], mapType[50];
            int yearsOfStorage = atoi(commandAndParameters[4]);
            strcpy(stateOfDeterioration, commandAndParameters[2]);
            strcpy(mapType, commandAndParameters[3]);
            if (updateMapService(ui->service, mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage) == 0) {
                printf("No!\n");
            }
        }else if(strcmp(commandAndParameters[0], "list") == 0) {
            if (commandAndParameters[1][0] == '\0') {
                char stringListOfMaps[1000] = "";
                listAllMaps(ui->service, stringListOfMaps);
                printf("%s", stringListOfMaps);
            } else if (strlen(commandAndParameters[1]) != 0 && commandAndParameters[2][0] == '\0') {
                char stringListOfMapsByType[1000] = "";
                listAllMapsByType(ui->service, commandAndParameters[1], stringListOfMapsByType);
                printf("%s", stringListOfMapsByType);
            }
        }else if (strcmp(commandAndParameters[0], "delete") == 0) {
            if (removeMapService(ui->service, commandAndParameters[1]) == 0) {
                printf("No!\n");
            }
        }
    }
}

UI createUI(Service *service) {
    UI result;
    result.service = service;
    return result;
}
