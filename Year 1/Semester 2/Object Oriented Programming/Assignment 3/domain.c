//
// Created by Octavian Custura on 04/03/2020.
//

#include "domain.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

Map createMap(int mapCatalogueNumber, char *stateOfDeterioration, char *mapType, int yearsOfStorage) {
    Map result;
    result.mapCatalogueNumber = mapCatalogueNumber;
    strcpy(result.stateOfDeterioration, stateOfDeterioration);
    strcpy(result.mapType, mapType);
    result.yearsOfStorage = yearsOfStorage;
    return result;
}

void changeStateOfDeterioration(Map *map, char* stateOfDeterioration) {
    strcpy(map->stateOfDeterioration, stateOfDeterioration);
}

void changeMapType(Map *map, char* mapType) {
    strcpy(map->mapType, mapType);
}

void changeYearsOfStorage(Map *map, int yearsOfStorage) {
    map->yearsOfStorage = yearsOfStorage;
}

char *getStateOfDeterioration(Map *map) {
    return map->stateOfDeterioration;
}

char *getMapType(Map *map) {
    return map->mapType;
}

int getYearsOfStorage(Map map) {
    return map.yearsOfStorage;
}

int getCatalogueNumber(Map map) {
    return map.mapCatalogueNumber;
}

void testMap() {
//    printf("Test map start\n");
    Map mapTest;
    mapTest = createMap(123, "abc", "def", 456);
    assert(getCatalogueNumber(mapTest) == 123);
    assert(getYearsOfStorage(mapTest) == 456);
    assert(strcmp(getMapType(&mapTest), "def") == 0);
    assert(strcmp(getStateOfDeterioration(&mapTest), "abc") == 0);
    changeMapType(&mapTest, "efg");
    assert(strcmp(getMapType(&mapTest), "efg") == 0);
    changeStateOfDeterioration(&mapTest, "xyz");
    assert(strcmp(getStateOfDeterioration(&mapTest), "xyz") == 0);
    changeYearsOfStorage(&mapTest, 999);
    assert(getYearsOfStorage(mapTest) == 999);
//    printf("Test map end\n");
}


