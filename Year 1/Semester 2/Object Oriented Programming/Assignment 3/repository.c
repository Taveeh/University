//
// Created by Octavian Custura on 04/03/2020.
//

#include "repository.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchMapInRepositoryByID(Repository *repository, int mapCatalogueNumber) {
    for (int indexMaps = 0; indexMaps < getLengthOfDynamicArray(repository->listOfMaps); ++indexMaps) {
        if (getElementOnPosition(repository->listOfMaps, indexMaps)->mapCatalogueNumber == mapCatalogueNumber) {
            return indexMaps;
        }
    }
    return -1;
}

void undoRepository(Repository* repository) {
    changeFlag(repository->undoRedo, 1);
    Operation* lastOperation = getLastUndo(repository->undoRedo);
    if (strcmp(getOperationType(lastOperation), "delete") == 0) {
        addRedo(repository->undoRedo, getMapFromOperation(lastOperation));
        deleteMapFromRepository(repository, getMapFromOperation(lastOperation)->mapCatalogueNumber);
    }else if (strcmp(getOperationType(lastOperation), "update") == 0) {
        updateMapFromRepository(repository, getMapFromOperation(lastOperation));
    }else if (strcmp(getOperationType(lastOperation), "add") == 0) {
        deleteRedo(repository->undoRedo, getMapFromOperation(lastOperation));
        addMapToRepository(repository, getMapFromOperation(lastOperation));
    }
//    destroyOperation(lastOperation);
    changeFlag(repository->undoRedo, 0);
}

void redoRepository(Repository* repository) {
    changeFlag(repository->undoRedo, 1);
    Operation* lastOperation = getLastRedo(repository->undoRedo);
    if (strcmp(getOperationType(lastOperation), "delete") == 0) {
        deleteUndo(repository->undoRedo, getMapFromOperation(lastOperation));
        deleteMapFromRepository(repository, getMapFromOperation(lastOperation)->mapCatalogueNumber);
    }else if (strcmp(getOperationType(lastOperation), "update") == 0){
        updateMapFromRepository(repository, getMapFromOperation(lastOperation));
    }else if (strcmp(getOperationType(lastOperation), "add") == 0) {
        addUndo(repository->undoRedo, getMapFromOperation(lastOperation));
        addMapToRepository(repository, getMapFromOperation(lastOperation));
    }
//    destroyOperation(lastOperation);
    changeFlag(repository->undoRedo, 0);
}

int addMapToRepository(Repository *repository, Map *map) {
    int indexMap = searchMapInRepositoryByID(repository, getCatalogueNumber(map));
    if (indexMap != -1) {
        return 0;
    }
    addUndo(repository->undoRedo, map);
    if (getFlag(repository->undoRedo) == 0) {
        clearRedo(repository->undoRedo);
    }
    addElementToDynamicArray(repository->listOfMaps, map);
    return 1;
}

int updateMapFromRepository(Repository *repository, Map* map) {
    int indexMap = searchMapInRepositoryByID(repository, map->mapCatalogueNumber);
    if (indexMap == -1) {
        return 0;
    }
    updateUndo(repository->undoRedo, getElementOnPosition(repository->listOfMaps, indexMap));
    updateRedo(repository->undoRedo, getElementOnPosition(repository->listOfMaps, indexMap));
    if (getFlag(repository->undoRedo) == 0) {
        clearRedo(repository->undoRedo);
    }
    deleteElementFromPosition(repository->listOfMaps, indexMap);
    insertElementToPosition(repository->listOfMaps, indexMap, map);
    return 1;
}

int deleteMapFromRepository(Repository *repository, int mapCatalogueNumber) {
    int indexMap = searchMapInRepositoryByID(repository, mapCatalogueNumber);
    if (indexMap == -1) {
        return 0;
    }
    deleteUndo(repository->undoRedo, (getElementOnPosition(repository->listOfMaps, indexMap)));
    if (getFlag(repository->undoRedo) == 0) {
        clearRedo(repository->undoRedo);
    }
    deleteElementFromPosition(repository->listOfMaps, indexMap);
    return 1;
}

Repository* createRepository() {
    Repository* result = (Repository*)malloc(sizeof(Repository));
    if (result == NULL) {
        return NULL;
    }
    result->listOfMaps = createDynamicArray(FIRST_CAPACITY);
    result->undoRedo = createUndoRedo();
    return result;
}

void destroyRepository(Repository *repository) {
    if (repository == NULL) {
        return;
    }
    destroyDynamicArray(repository->listOfMaps);
    destroyUndoRedo(repository->undoRedo);
    free(repository);
}

int getRepositoryLength(Repository *repository) {
    return getLengthOfDynamicArray(repository->listOfMaps);
}
