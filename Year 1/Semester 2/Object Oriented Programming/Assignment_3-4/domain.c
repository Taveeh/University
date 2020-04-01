//
// Created by Octavian Custura on 04/03/2020.
//

#include "domain.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

Map* createMap(int mapCatalogueNumber, char *stateOfDeterioration, char *mapType, int yearsOfStorage) {
    Map* result = (Map*)malloc(sizeof(Map));
    result->mapCatalogueNumber = mapCatalogueNumber;
    result->stateOfDeterioration = (char*)malloc(sizeof(char) * (strlen(stateOfDeterioration) + 1));
    strcpy(result->stateOfDeterioration, stateOfDeterioration);
    result->mapType = (char*)malloc(sizeof(char) * (strlen(mapType) + 1));
    strcpy(result->mapType, mapType);
    result->yearsOfStorage = yearsOfStorage;
    return result;
}

void changeStateOfDeterioration(Map *map, char* stateOfDeterioration) {
    if (map == NULL || strlen(stateOfDeterioration) == 0) {
        return;
    }
    free(map->stateOfDeterioration);
    map->stateOfDeterioration = (char*)malloc(sizeof(char) * strlen(stateOfDeterioration) + 1);
    strcpy(map->stateOfDeterioration, stateOfDeterioration);
}

void changeMapType(Map *map, char* mapType) {
    if (map == NULL || strlen(mapType) == 0) {
        return;
    }
    free(map->mapType);
    map->mapType = (char*) malloc(sizeof(char) * strlen(mapType) + 1);
    strcpy(map->mapType, mapType);
}

void changeYearsOfStorage(Map *map, int yearsOfStorage) {
    if (map == NULL || yearsOfStorage < 0) {
        return;
    }
    map->yearsOfStorage = yearsOfStorage;
}

char *getStateOfDeterioration(Map *map) {
    if (map == NULL) {
        return NULL;
    }
    return map->stateOfDeterioration;
}

char *getMapType(Map *map) {
    if (map == NULL) {
        return NULL;
    }
    return map->mapType;
}

int getYearsOfStorage(Map *map) {
    if (map == NULL) {
        return -1;
    }
    return map->yearsOfStorage;
}

int getCatalogueNumber(Map *map) {
    if (map == NULL) {
        return -1;
    }
    return map->mapCatalogueNumber;
}

void destroyMap(Map *map) {
    if (map == NULL) {
        return;
    }
    free(map->mapType);
    free(map->stateOfDeterioration);
    free(map);
    map = NULL;
}

Map *copyMap(Map *map) {
    return createMap(getCatalogueNumber(map), getStateOfDeterioration(map), getMapType(map), getYearsOfStorage(map));
}


