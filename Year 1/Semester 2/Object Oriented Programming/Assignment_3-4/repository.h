//
// Created by Octavian Custura on 04/03/2020.
//

#pragma once

#include "domain.h"
#include "dynamicArray.h"
#include "undoRedo.h"

typedef struct {
    DynamicArray* listOfMaps;
} Repository;

/*
 * Constructor
 */
Repository* createRepository();

/*
 * Add map to repository
 * Input:
 * Map* map
 * Repository* repository
 * Output:
 * 1 - if added
 * 0 - otherwise
 */
int addMapToRepository(Repository* repository, Map* map);

/*
 * Update a map from repository
 * Input:
 * Map* map
 * Repository* repository
 * Output:
 * 1 - if modified
 * 0 - otherwise
 */
int updateMapFromRepository(Repository* repository, Map* map);

/*
 * Remove map from repository
 * Input:
 * int - catalogue number
 * Repository* repository
 * Output:
 * 1 - if removed
 * 0 - otherwise
 */
int deleteMapFromRepository(Repository* repository, int mapCatalogueNumber);

/*
 * Search for catalogue number in Repository
 * Input:
 * Repository*
 * Int - catalogue number
 * Output:
 * int - position -- if found
 * -1 otherwise
 */
int searchMapInRepositoryByID(Repository* repository, int mapCatalogueNumber);

/*
 * Destructor
 */
void destroyRepository(Repository* repository);

/*
 * Return length of repository
 * Input:
 * Repository *repository
 * Output:
 * Int - length
 */
int getRepositoryLength(Repository* repository);

/*
 * Function that undoes the last operation
 * Input:
 * Repository*
 */
void undoRepository(Repository* repository);

/*
 * Function that redoes the last undo
 * Input:
 * Repository*
 */
void redoRepository(Repository* repository);

/*
 * Function that gets the element on given position
 * Input:
 * Repository*
 * int - position
 * Output:
 * Map* - element on position position
 */
Map* getElementOnPositionRepository(Repository* repository, int position);

void setNewArray(Repository* repository, DynamicArray* dynamicArray);

DynamicArray* getRepositoryElements(Repository* repository);