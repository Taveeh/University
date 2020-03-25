//
// Created by Octavian Custura on 04/03/2020.
//
#pragma once

#include "repository.h"
#include "undoRedo.h"
#include "newUndoRedo.h"

typedef struct {
    Repository* repository;
    UndoRedoNew * undoRedo;
} Service;

/*
 * Constructor
 */
Service* createService(Repository* repository);

/*
 * Destructor
 */
void destroyService(Service* service);

/*
 * Add a map to a service
 * Input:
 * Service*
 * map catalogue number - int
 * state of deterioration - char*
 * map type - char*
 * years of storage - int
 * Output:
 * 1 - if added
 * 0 - otherwise
 */
int addMapService(Service *service, int mapCatalogueNumber, char *stateOfDeterioration, char *mapType, int yearsOfStorage);

/*
 * Removes a map from service
 * Input:
 * Service*
 * CatalogueNumberString - char*
 * Output:
 * 1 - if removed
 * 0 - otherwise
 */
int removeMapService(Service *service, char *mapCatalogueNumberString);

/*
 * Update a map from service
 * Input:
 * Service*
 * map catalogue number - int
 * state of deterioration - char*
 * map type - char*
 * years of storage - int
 * Output:
 * 1 - if updated
 * 0 - otherwise
 */
int updateMapService(Service *service, int mapCatalogueNumber, char *stateOfDeterioration, char *mapType, int yearsOfStorage);

/*
 * Function that gives all maps in service
 * Input:
 * Service*
 * DynamicArray* list of all maps
 */
void listAllMaps(Service *service, DynamicArray* listOfAllMapsString);

/*
 * Function that filters maps with given property regarding map type
 * Input:
 * Service*
 * map type - char*
 * DynamicArray* - list of all maps with given property
 * property - function returning int
 */
void listAllMapsByType(Service* service, char* mapType, DynamicArray* listOfAllMapsByPropertyString,  int (*property)(Map*, char*));

/*
 * Function that sorts elements lower than a given age
 * Input:
 * Service*
 * ageLimit - int
 * DynamicArray* - sorted list of elements
 * reverse - function returning int
 */
void sortMapsLowerThanAge(Service* service, int ageLimit, DynamicArray* sortedListOfMaps, int (*reverse)(Map*, Map*));

/*
 * Undo the last operation
 * Input:
 * Service*
 */
void undoLastOperation(Service* service);

/*
 * Redo operation
 * Input:
 * Service*
 */
void redoLastOperation(Service* service);

void undoLastOperationNew(Service* service);

void redoLastOperationNew(Service* service);
