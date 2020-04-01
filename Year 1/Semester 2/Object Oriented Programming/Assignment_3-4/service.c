//
// Created by Octavian Custura on 04/03/2020.
//

#include "service.h"
#include "repository.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int addMapService(Service *service,int mapCatalogueNumber, char *stateOfDeterioration, char *mapType, int yearsOfStorage) {
    Map* map = createMap(mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage);
//    addUndo(service->undoRedo, map);
//    if (getFlag(service->undoRedo)) {
//        clearRedo(service->undoRedo);
//    }
    addUndoNew(service->undoRedo, copyDynamicArray(getRepositoryElements(service->repository)));
    if (addMapToRepository(service->repository, map) == 0) {
        undoFunction(service->undoRedo);
        destroyMap(map);
        return 0;
    }
    return 1;
}

Service* createService(Repository *repository) {
    Service* result = (Service*)malloc(sizeof(Service));
    result->repository = repository;
    result->undoRedo = createUndoRedoNew();
    return result;

}

int removeMapService(Service *service, char *mapCatalogueNumberString) {
    int mapCatalogueNumber = atoi(mapCatalogueNumberString);
    addUndoNew(service->undoRedo, copyDynamicArray(getRepositoryElements(service->repository)));
    if (deleteMapFromRepository(service->repository, mapCatalogueNumber)== 0) {
        undoFunction(service->undoRedo);
        return 0;
    }
    return 1;
}

int updateMapService(Service *service, int mapCatalogueNumber, char *stateOfDeterioration, char *mapType,
                     int yearsOfStorage) {
    Map *map = createMap(mapCatalogueNumber, stateOfDeterioration, mapType, yearsOfStorage);
//    updateUndo(service->undoRedo, map);
//    if (getFlag(service->undoRedo)) {
//        clearRedo(service->undoRedo);
//    }
    addUndoNew(service->undoRedo, copyDynamicArray(getRepositoryElements(service->repository)));
    if (updateMapFromRepository(service->repository, map) == 0) {
        undoFunction(service->undoRedo);
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
//    destroyUndoRedo(service->undoRedo);
    destroyNewUndoRedo(service->undoRedo);
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
        if (((Map*)currentElement)->yearsOfStorage < ageLimit) {
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

char* integerToChar(int numberToBeConverted, char* stringConverted) {
    sprintf(stringConverted, "%d", numberToBeConverted);
    return stringConverted;
}
//
//void undoLastOperation(Service* service) {
//    changeFlag(service->undoRedo, 1);
//    Operation* lastOperation = getLastUndo(service->undoRedo);
//    if (strcmp(getOperationType(lastOperation), "delete") == 0) {
//        addRedo(service->undoRedo, getMapFromOperation(lastOperation));
//        char stringToConvert[20];
//        removeMapService(service, integerToChar(getMapFromOperation(lastOperation)->mapCatalogueNumber, stringToConvert));
//    }else if (strcmp(getOperationType(lastOperation), "update") == 0) {
//        updateMapService(service, getCatalogueNumber(getMapFromOperation(lastOperation)), getStateOfDeterioration(getMapFromOperation(lastOperation)), getMapType(getMapFromOperation(lastOperation)), getYearsOfStorage(getMapFromOperation(lastOperation)));
//    }else if (strcmp(getOperationType(lastOperation), "add") == 0) {
//        deleteRedo(service->undoRedo, getMapFromOperation(lastOperation));
//        addMapService(service, getCatalogueNumber(getMapFromOperation(lastOperation)), getStateOfDeterioration(getMapFromOperation(lastOperation)), getMapType(getMapFromOperation(lastOperation)), getYearsOfStorage(getMapFromOperation(lastOperation)));
//    }
//    changeFlag(service->undoRedo, 0);
//}
//
//void redoLastOperation(Service* service) {
//    changeFlag(service->undoRedo, 1);
//    Operation* lastOperation = getLastRedo(service->undoRedo);
//    if (strcmp(getOperationType(lastOperation), "delete") == 0) {
//        deleteUndo(service->undoRedo, getMapFromOperation(lastOperation));
//        char stringToConvert[20];
//        removeMapService(service, integerToChar(getMapFromOperation(lastOperation)->mapCatalogueNumber, stringToConvert));
//    }else if (strcmp(getOperationType(lastOperation), "update") == 0){
//        updateMapService(service, getCatalogueNumber(getMapFromOperation(lastOperation)), getStateOfDeterioration(getMapFromOperation(lastOperation)), getMapType(getMapFromOperation(lastOperation)), getYearsOfStorage(getMapFromOperation(lastOperation)));
//    }else if (strcmp(getOperationType(lastOperation), "add") == 0) {
//        addUndo(service->undoRedo, getMapFromOperation(lastOperation));
//        addMapService(service, getCatalogueNumber(getMapFromOperation(lastOperation)), getStateOfDeterioration(getMapFromOperation(lastOperation)), getMapType(getMapFromOperation(lastOperation)), getYearsOfStorage(getMapFromOperation(lastOperation)));
//    }
//    changeFlag(service->undoRedo, 0);
//}

void undoLastOperationNew(Service* service) {
    if (firstCall(service->undoRedo)) {
        addUndoNew(service->undoRedo, copyDynamicArray(getRepositoryElements(service->repository)));
    }
    setNewArray(service->repository, undoFunction(service->undoRedo));
}

void redoLastOperationNew(Service *service) {
    setNewArray(service->repository, redoFunction(service->undoRedo));
}


