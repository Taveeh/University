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
        if (((Map*)getElementOnPosition(repository->listOfMaps, indexMaps))->mapCatalogueNumber == mapCatalogueNumber) {
            return indexMaps;
        }
    }
    return -1;
}

int addMapToRepository(Repository *repository, Map *map) {
    int indexMap = searchMapInRepositoryByID(repository, getCatalogueNumber(map));
    if (indexMap != -1) {
        return 0;
    }

    addElementToDynamicArray(repository->listOfMaps, map);
    return 1;
}

int updateMapFromRepository(Repository *repository, Map* map) {
    int indexMap = searchMapInRepositoryByID(repository, map->mapCatalogueNumber);
    if (indexMap == -1) {
        return 0;
    }
//    updateUndo(repository->undoRedo, getElementOnPosition(repository->listOfMaps, indexMap));
//    updateRedo(repository->undoRedo, getElementOnPosition(repository->listOfMaps, indexMap));
//    if (getFlag(repository->undoRedo) == 0) {
//        clearRedo(repository->undoRedo);
//    }
    deleteElementFromPosition(repository->listOfMaps, indexMap);
    insertElementToPosition(repository->listOfMaps, indexMap, map);
    return 1;
}

Map* getElementOnPositionRepository(Repository* repository, int position) {
    return getElementOnPosition(repository->listOfMaps, position);
}

int deleteMapFromRepository(Repository *repository, int mapCatalogueNumber) {
    int indexMap = searchMapInRepositoryByID(repository, mapCatalogueNumber);
    if (indexMap == -1) {
        return 0;
    }
//    deleteUndo(repository->undoRedo, getElementOnPosition(repository->listOfMaps, indexMap));
//    if (getFlag(repository->undoRedo) == 0) {
//        clearRedo(repository->undoRedo);
//    }
    deleteElementFromPosition(repository->listOfMaps, indexMap);
    return 1;
}

Repository* createRepository() {
    Repository* result = (Repository*)malloc(sizeof(Repository));
    if (result == NULL) {
        return NULL;
    }
    result->listOfMaps = createDynamicArray(FIRST_CAPACITY, &destroyMap, &copyMap);
    return result;
}

void destroyRepository(Repository *repository) {
    if (repository == NULL) {
        return;
    }
    destroyDynamicArray(repository->listOfMaps);
    repository->listOfMaps = NULL;
    free(repository);
}

int getRepositoryLength(Repository *repository) {
    return getLengthOfDynamicArray(repository->listOfMaps);
}

void setNewArray(Repository *repository, DynamicArray *dynamicArray) {
    repository->listOfMaps = copyDynamicArray(dynamicArray);
//    repository->listOfMaps = dynamicArray;
}

DynamicArray *getRepositoryElements(Repository *repository) {
    return repository->listOfMaps;
}
