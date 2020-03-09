//
// Created by Octavian Custura on 04/03/2020.
//
#pragma once

#include "repository.h"
typedef struct {
    Repository* repository;
} Service;

Service createService(Repository* repository);

int addMapService(Service *service, int mapCatalogueNumber, char stateOfDeterioration[50], char mapType[50], int yearsOfStorage);

int removeMapService(Service *service, char mapCatalogueNumberString[]);

int updateMapService(Service *service, int mapCatalogueNumber, char stateOfDeterioration[50], char mapType[50], int yearsOfStorage);

void listAllMaps(Service *service, char listOfAllMapsString[]);

void testService();

void listAllMapsByType(Service* service, char mapType[], char listOfAllMapsByPropertyString[]);

void integerToString(int numberToBeConvertedToString, char convertedString[]);