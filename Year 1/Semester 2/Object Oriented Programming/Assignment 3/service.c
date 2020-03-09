//
// Created by Octavian Custura on 04/03/2020.
//

#include "service.h"
#include "repository.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int addMapService(Service *service,int mapCatalogueNumber, char *stateOfDeterioration, char *mapType, int yearsOfStorage) {
    Map map = createMap(mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage);
    if (addMapToRepository(service->repository, map) == 0) {
        return 0;
    }
    return 1;
}

Service createService(Repository *repository) {
    Service result;
    result.repository = repository;
    return result;
}

int removeMapService(Service *service, char mapCatalogueNumberString[50]) {
    int mapCatalogueNumber = atoi(mapCatalogueNumberString);
    if (deleteMapFromRepository(service->repository, mapCatalogueNumber)== 0) {
        return 0;
    }
    return 1;
}

int updateMapService(Service *service, int mapCatalogueNumber, char *stateOfDeterioration, char *mapType,
                     int yearsOfStorage) {
    Map map = createMap(mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage);
    if (updateMapFromRepository(service->repository, &map) == 0) {
        return 0;
    }
    return 1;
}

void testService() {
//    printf("Test service start\n");
    Repository repository = createRepository();
    Service service = createService(&repository);
    assert(addMapService(&service, 123, "abc", "def", 456) == 1);
    assert(addMapService(&service, 123, "abc", "def", 456) == 0);
    assert(service.repository->numberOfMaps == 1);
    assert(updateMapService(&service, 123, "bcd", "efg", 999) == 1);
    assert(getYearsOfStorage(service.repository->listOfMaps[0]) == 999);
    assert(strcmp(getStateOfDeterioration(&service.repository->listOfMaps[0]), "bcd") == 0);
    assert(removeMapService(&service, "123") == 1);
    assert(removeMapService(&service, "123") == 0);
//    printf("Test service end\n");
}

void listAllMaps(Service *service, char listOfAllMapsString[]) {
    for (int i = 0; i < service->repository->numberOfMaps; ++i) {
        strcat(listOfAllMapsString, "Map catalogue number: ");
        char mapCatalogueNumberString[10];
        integerToString(getCatalogueNumber(service->repository->listOfMaps[i]), mapCatalogueNumberString);
        strcat(listOfAllMapsString, mapCatalogueNumberString);
        strcat(listOfAllMapsString, ", State of deterioration:  ");
        strcat(listOfAllMapsString, getStateOfDeterioration(&service->repository->listOfMaps[i]));
        strcat(listOfAllMapsString, ", Map Type: ");
        strcat(listOfAllMapsString, getMapType(&service->repository->listOfMaps[i]));
        strcat(listOfAllMapsString, ", Years of storage: ");
        char yearsOfStorageString[10];
        integerToString(getYearsOfStorage(service->repository->listOfMaps[i]), yearsOfStorageString);
        strcat(listOfAllMapsString, yearsOfStorageString);
        strcat(listOfAllMapsString, "\n");
    }
}

void integerToString(int numberToBeConvertedToString, char *convertedString) {
    sprintf(convertedString, "%d", numberToBeConvertedToString);
}

void listAllMapsByType(Service *service, char *mapType, char *listOfAllMapsByPropertyString) {
    for (int i = 0; i < service->repository->numberOfMaps; ++i) {
        if (strcmp(mapType, getMapType(&service->repository->listOfMaps[i])) == 0) {
            strcat(listOfAllMapsByPropertyString, "Map catalogue number: ");
            char mapCatalogueNumberString[10];
            integerToString(getCatalogueNumber(service->repository->listOfMaps[i]), mapCatalogueNumberString);
            strcat(listOfAllMapsByPropertyString, mapCatalogueNumberString);
            strcat(listOfAllMapsByPropertyString, ", State of deterioration: ");
            strcat(listOfAllMapsByPropertyString, getStateOfDeterioration(&service->repository->listOfMaps[i]));
            strcat(listOfAllMapsByPropertyString, ", Map Type: ");
            strcat(listOfAllMapsByPropertyString, getMapType(&service->repository->listOfMaps[i]));
            strcat(listOfAllMapsByPropertyString, ", Years of storage: ");
            char yearsOfStorageString[10];
            integerToString(getYearsOfStorage(service->repository->listOfMaps[i]), yearsOfStorageString);
            strcat(listOfAllMapsByPropertyString, yearsOfStorageString);
            strcat(listOfAllMapsByPropertyString, "\n");
        }
    }
}

