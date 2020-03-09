//
// Created by Octavian Custura on 04/03/2020.
//
#pragma once
typedef struct {
    int mapCatalogueNumber;
    char stateOfDeterioration[50], mapType[50];
    int yearsOfStorage;
} Map;

/*
 *
 * Map constructor
 *
 * Input:
 * mapCatalogueNumber - int
 * stateOfDeterioration - array of characters
 * mapType - array of characters
 * yearsOfStorage - int
 *
 * Output:
 * map - Map
 *
 */
Map createMap(int mapCatalogueNumber, char stateOfDeterioration[50], char mapType[50], int yearsOfStorage);

/*
 *
 * Changes the state of deterioration of a map
 *
 * Input:
 * map - Pointer to Map
 * stateOfDeterioration - array of characters
 *
 */
void changeStateOfDeterioration(Map* map, char stateOfDeterioration[50]);

/*
 *
 * Change type of a map
 * 
 */
void changeMapType(Map* map, char mapType[50]);

void changeYearsOfStorage(Map* map, int yearsOfStorage);

void testMap();

char* getStateOfDeterioration(Map* map);

char* getMapType(Map* map);

int getYearsOfStorage(Map map);

int getCatalogueNumber(Map map);