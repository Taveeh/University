//
// Created by Octavian Custura on 04/03/2020.
//
#pragma once
typedef struct {
    int mapCatalogueNumber;
    char *stateOfDeterioration, *mapType;
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
Map* createMap(int mapCatalogueNumber, char *stateOfDeterioration, char *mapType, int yearsOfStorage);

Map* copyMap(Map* map);

/*
 *
 * Changes the state of deterioration of a map
 *
 * Input:
 * map - Pointer to Map
 * stateOfDeterioration - array of characters
 *
 */
void changeStateOfDeterioration(Map* map, char *stateOfDeterioration);

/*
 *
 * Change type of a map
 * Input:
 * mapType - Pointer to Char
 * map - pointer to map
 * Output:
 *
 */
void changeMapType(Map* map, char *mapType);

/*
 *
 * Change years of storage of a map
 * Input:
 * map - Pointer to map
 * yearsOfStorage - int
 * Output:
 *
 */
void changeYearsOfStorage(Map* map, int yearsOfStorage);

/*
 *
 * Get state of deterioration of a map
 * Input:
 * map - Pointer to map
 * Output:
 * stateOfDeterioration - pointer to char
 *
 */
char* getStateOfDeterioration(Map* map);

/*
 *
 * Get type of a map
 * Input:
 * map - Pointer to map
 * Output:
 * mapType - pointer to char
 *
 */
char* getMapType(Map* map);

/*
 *
 * Get years of storage of a map
 * Input:
 * map - pointer to map
 * Output:
 * yearsOfStorage - int
 *
 */
int getYearsOfStorage(Map* map);

/*
 *
 * Get catalogue number of a map
 * Input:
 * map - pointer to map
 * Output:
 * catalogueNumber - int
 *
 */
int getCatalogueNumber(Map* map);

/*
 *
 * Destructor
 * Input:
 * map - pointer to map
 * Output:
 *
 */
void destroyMap(Map* map);