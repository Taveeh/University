//
// Created by Octavian Custura on 04/03/2020.
//

#include "service.h"
#include "repository.h"
#include <string.h>
#include <stdlib.h>

int addMapService(Service *service,int mapCatalogueNumber, char *stateOfDeterioration, char *mapType, int yearsOfStorage) {
    Map* map = createMap(mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage);
    if (addMapToRepository(service->repository, map) == 0) {
        destroyMap(map);
        return 0;
    }
    return 1;
}

Service* createService(Repository *repository) {
    Service* result = (Service*)malloc(sizeof(Service));
    result->repository = repository;
    return result;
}

int removeMapService(Service *service, char *mapCatalogueNumberString) {
    int mapCatalogueNumber = atoi(mapCatalogueNumberString);
    if (deleteMapFromRepository(service->repository, mapCatalogueNumber)== 0) {
        return 0;
    }
    return 1;
}

int updateMapService(Service *service, int mapCatalogueNumber, char *stateOfDeterioration, char *mapType,
                     int yearsOfStorage) {
    Map *map = createMap(mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage);
    if (updateMapFromRepository(service->repository, map) == 0) {
        destroyMap(map);
        return 0;
    }
    return 1;
}

void destroyService(Service *service) {
    if (service == NULL) {
        return;
    }
    destroyRepository(service->repository);
    free(service);
}

void listAllMaps(Service *service, DynamicArray *listOfAllMapsString) {
    for (int mapIndex = 0; mapIndex < getRepositoryLength(service->repository); ++mapIndex) {
        TypeOfElement currentElement = getElementOnPositionRepository(service->repository, mapIndex);
        TypeOfElement auxiliary = createMap(getCatalogueNumber(currentElement), getStateOfDeterioration(currentElement), getMapType(currentElement), getYearsOfStorage(currentElement));
        addElementToDynamicArray(listOfAllMapsString, auxiliary);
    }
}

void listAllMapsByType(Service *service, char* mapType, DynamicArray *listOfAllMapsByPropertyString, int (*property)(Map*, char*)) {
    if (property == NULL || mapType == NULL) {
        return;
    }
    for (int mapIndex = 0; mapIndex < getRepositoryLength(service->repository); ++mapIndex) {
        TypeOfElement currentElement = getElementOnPositionRepository(service->repository, mapIndex);
        if (property(currentElement, mapType) == 1) {
            TypeOfElement auxiliary = createMap(getCatalogueNumber(currentElement), getStateOfDeterioration(currentElement), getMapType(currentElement), getYearsOfStorage(currentElement));
            addElementToDynamicArray(listOfAllMapsByPropertyString, auxiliary);
        }
    }
}

void sortMapsLowerThanAge(Service *service, int ageLimit, DynamicArray *sortedListOfMaps, int (*reverse)(Map*, Map*)) {
    if (reverse == NULL || ageLimit <= 0) {
        return;
    }
    for (int mapIndex = 0; mapIndex < getRepositoryLength(service->repository); ++mapIndex) {
        TypeOfElement currentElement = getElementOnPositionRepository(service->repository, mapIndex);
        if (currentElement->yearsOfStorage < ageLimit) {
            TypeOfElement auxiliary = createMap(getCatalogueNumber(currentElement),
                                                getStateOfDeterioration(currentElement), getMapType(currentElement),
                                                getYearsOfStorage(currentElement));
            if (getLengthOfDynamicArray(sortedListOfMaps) == 0) {
                addElementToDynamicArray(sortedListOfMaps, auxiliary);
            } else {
                    int positionToInsert = getLengthOfDynamicArray(sortedListOfMaps) ;
                    while (positionToInsert >= 1 && reverse(currentElement, getElementOnPosition(sortedListOfMaps, positionToInsert - 1)) == 1) {
                        positionToInsert--;
                    }
                    insertElementToPosition(sortedListOfMaps, positionToInsert, auxiliary);
                }
            }
        }
    }

void undoLastOperation(Service *service) {
    undoRepository(service->repository);
}

void redoLastOperation(Service *service) {
    redoRepository(service->repository);
}



