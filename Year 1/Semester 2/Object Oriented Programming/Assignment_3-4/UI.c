//
// Created by Octavian Custura on 06/03/2020.
//

#include "UI.h"
#include "functionForFilterAndSort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define MAX_COMMAND_SIZE 256
#define MAX_STRING_SIZE 1000
#define INDEX_OF_COMMAND 0
#define INDEX_MAP_ID 1
#define INDEX_MAP_STATE_OF_DETERIORATION 2
#define INDEX_MAP_TYPE 3
#define INDEX_MAP_YEARS_OF_STORAGE 4
#define INDEX_SPECIAL_LIST 1
#define MAX_NUMBER_COMMAND_PARAMETERS 5
#define SPECIAL_PROPERTY 2
void parseReading(char* stringToBeParsed, char** parsedArrayOfStrings) {
    char *pointerForParsingUserInputCommand;
    pointerForParsingUserInputCommand = strtok(stringToBeParsed, " ");
    int indexWordFromCommands = INDEX_OF_COMMAND;
    while (pointerForParsingUserInputCommand != NULL) {
        strcpy(parsedArrayOfStrings[indexWordFromCommands++], pointerForParsingUserInputCommand);
        pointerForParsingUserInputCommand = strtok(NULL, " ");
    }
    if (strcmp(parsedArrayOfStrings[INDEX_OF_COMMAND], "add") == 0 || strcmp(parsedArrayOfStrings[INDEX_OF_COMMAND], "update") == 0) {
        for (int wordInParsedString = INDEX_MAP_STATE_OF_DETERIORATION; wordInParsedString < INDEX_MAP_YEARS_OF_STORAGE; ++wordInParsedString) {
            parsedArrayOfStrings[wordInParsedString][strlen(
                    parsedArrayOfStrings[wordInParsedString]) - 1] = '\0';
        }
    }
}


void readUserCommand(UI *ui) {
    char userCommand[MAX_COMMAND_SIZE];
    char** commandAndParameters = (char**)malloc(MAX_NUMBER_COMMAND_PARAMETERS * sizeof(char*));
    for (int i = 0; i < MAX_NUMBER_COMMAND_PARAMETERS; ++i) {
        commandAndParameters[i] = (char*)malloc(sizeof(char) * MAX_SIZE);
    }
    while(1) {
        scanf("%[^\n]%*c", userCommand);
        for (int i = INDEX_OF_COMMAND; i < MAX_NUMBER_COMMAND_PARAMETERS; ++i) {
            commandAndParameters[i][0] = '\0';
        }
        parseReading(userCommand, commandAndParameters);
        if (strcmp(commandAndParameters[INDEX_OF_COMMAND], "exit") == 0) {
            break;
        }
        if (strcmp(commandAndParameters[INDEX_OF_COMMAND], "add") == 0) {
            addMapUI(ui, commandAndParameters);
        } else if (strcmp(commandAndParameters[INDEX_OF_COMMAND], "update") == 0) {
            updateMapUI(ui, commandAndParameters);
        }else if(strcmp(commandAndParameters[INDEX_OF_COMMAND], "list") == 0) {
            if (commandAndParameters[INDEX_SPECIAL_LIST][0] == '\0') {
                listAllMapsUI(ui, commandAndParameters);
            } else if (strlen(commandAndParameters[INDEX_SPECIAL_LIST]) != 0) {
                int ageOfSorting = atoi(commandAndParameters[INDEX_SPECIAL_LIST]);
                if (ageOfSorting != 0) {
                    sortByAgeUI(ui, commandAndParameters);
                }else {
                    listAllMapsUIByType(ui, commandAndParameters);
                }
            }
        }else if (strcmp(commandAndParameters[INDEX_OF_COMMAND], "delete") == 0) {
            removeMapUI(ui, commandAndParameters);
        } else if (strcmp(commandAndParameters[INDEX_OF_COMMAND], "undo") == 0) {
            undoOperationUI(ui);
        } else if (strcmp(commandAndParameters[INDEX_OF_COMMAND], "redo") == 0) {
            redoOperationUI(ui);
        } else {
            printf("Invalid command\n");
        }
    }
    for (int i = 0; i < MAX_NUMBER_COMMAND_PARAMETERS; ++i) {
        free(commandAndParameters[i]);
    }
    free(commandAndParameters);
}

UI* createUI(Service *service) {
    UI* result = (UI*)malloc(sizeof(UI));
    result->service = service;
    return result;
}

void destroyUI(UI *ui) {
    destroyService(ui->service);
    free(ui);
}


void addMapUI(UI *ui, char *(*parsedArrayOfStrings)) {
    int mapCatalogueNumber = atoi(parsedArrayOfStrings[1]);
    char stateOfDeterioration[MAX_SIZE], mapType[MAX_SIZE];
    int yearsOfStorage = atoi(parsedArrayOfStrings[INDEX_MAP_YEARS_OF_STORAGE]);
    strcpy(stateOfDeterioration, parsedArrayOfStrings[INDEX_MAP_STATE_OF_DETERIORATION]);
    strcpy(mapType, parsedArrayOfStrings[INDEX_MAP_TYPE]);
    if (addMapService(ui->service, mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage) == 0) {
        printf("No!\n");
    }
}

void updateMapUI(UI *ui, char *(*parsedArrayOfStrings)) {
    int mapCatalogueNumber = atoi(parsedArrayOfStrings[INDEX_MAP_ID]);
    char stateOfDeterioration[MAX_SIZE], mapType[MAX_SIZE];
    int yearsOfStorage = atoi(parsedArrayOfStrings[INDEX_MAP_YEARS_OF_STORAGE]);
    strcpy(stateOfDeterioration, parsedArrayOfStrings[INDEX_MAP_STATE_OF_DETERIORATION]);
    strcpy(mapType, parsedArrayOfStrings[INDEX_MAP_TYPE]);
    if (updateMapService(ui->service, mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage) == 0) {
        printf("No!\n");
    }
}

void listAllMapsUI(UI *ui, char *(*parsedArrayOfStrings)) {
    DynamicArray* stringListOfMaps = createDynamicArray(MAX_STRING_SIZE, &destroyMap, &copyMap);
    listAllMaps(ui->service, stringListOfMaps);
    for (int mapIndex = 0; mapIndex < getLengthOfDynamicArray(stringListOfMaps); ++mapIndex) {
        printf("Map Catalogue Number: %d, State of Deterioration: %s, Map Type: %s, Years of Storage: %d\n", getCatalogueNumber(stringListOfMaps->dynamicArrayElements[mapIndex]), getStateOfDeterioration(stringListOfMaps->dynamicArrayElements[mapIndex]), getMapType(stringListOfMaps->dynamicArrayElements[mapIndex]), getYearsOfStorage(stringListOfMaps->dynamicArrayElements[mapIndex]));
    }
    destroyDynamicArray(stringListOfMaps);
}

void listAllMapsUIByType(UI *ui, char *(*parsedArrayOfStrings)) {
    int (*functionToFilterList)();
    if (parsedArrayOfStrings[SPECIAL_PROPERTY][0] == '\0') {
        functionToFilterList = &selectIfSameMapType;
    } else if (strcmp(parsedArrayOfStrings[SPECIAL_PROPERTY], "inclusion") == 0) {
        functionToFilterList = &selectIfMapTypeIsSubTypeOfGivenType;
    }else {
        functionToFilterList = &selectAllForAmbiguity;
    }
    DynamicArray* stringListOfMapsByType = createDynamicArray(MAX_STRING_SIZE, &destroyMap, &copyMap);
    listAllMapsByType(ui->service, parsedArrayOfStrings[INDEX_SPECIAL_LIST], stringListOfMapsByType, functionToFilterList);
    for (int mapIndex = 0; mapIndex < getLengthOfDynamicArray(stringListOfMapsByType); ++mapIndex) {
        printf("Map Catalogue Number: %d, State of Deterioration: %s, Map Type: %s, Years of Storage: %d\n", getCatalogueNumber(stringListOfMapsByType->dynamicArrayElements[mapIndex]), getStateOfDeterioration(stringListOfMapsByType->dynamicArrayElements[mapIndex]), getMapType(stringListOfMapsByType->dynamicArrayElements[mapIndex]), getYearsOfStorage(stringListOfMapsByType->dynamicArrayElements[mapIndex]));
    }
    destroyDynamicArray(stringListOfMapsByType);
}

void removeMapUI(UI *ui, char *(*parsedArrayOfStrings)) {
    if (removeMapService(ui->service, parsedArrayOfStrings[INDEX_MAP_ID]) == 0) {
        printf("No!\n");
    }
}

void sortByAgeUI(UI* ui, char** parsedArrayOfStrings) {
    int (*functionToSortList)();
    int ageOfSorting = atoi(parsedArrayOfStrings[INDEX_SPECIAL_LIST]);
    if (strcmp(parsedArrayOfStrings[SPECIAL_PROPERTY], "reverse") == 0) {
        functionToSortList = &reverseSorting;
    }else {
        functionToSortList = &normalSorting;
    }
    DynamicArray* sortedArrayOfMapsLowerThanAge = createDynamicArray(MAX_STRING_SIZE, &destroyMap, &copyMap);
    sortMapsLowerThanAge(ui->service, ageOfSorting, sortedArrayOfMapsLowerThanAge, functionToSortList);
    for (int mapIndex = 0; mapIndex < getLengthOfDynamicArray(sortedArrayOfMapsLowerThanAge); ++mapIndex) {
        printf("Map Catalogue Number: %d, State of Deterioration: %s, Map Type: %s, Years of Storage: %d\n", getCatalogueNumber(sortedArrayOfMapsLowerThanAge->dynamicArrayElements[mapIndex]), getStateOfDeterioration(sortedArrayOfMapsLowerThanAge->dynamicArrayElements[mapIndex]), getMapType(sortedArrayOfMapsLowerThanAge->dynamicArrayElements[mapIndex]), getYearsOfStorage(sortedArrayOfMapsLowerThanAge->dynamicArrayElements[mapIndex]));
    }
}

void undoOperationUI(UI *ui){
//    undoLastOperation(ui->service);
    undoLastOperationNew(ui->service);
}


void redoOperationUI(UI* ui) {
//    redoLastOperation(ui->service);
    redoLastOperationNew(ui->service);
}