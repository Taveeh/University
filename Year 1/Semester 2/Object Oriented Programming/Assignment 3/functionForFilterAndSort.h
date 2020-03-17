//
// Created by Octavian Custura on 17/03/2020.
//

#pragma once

#include "domain.h"

/*
 * Function to select elements that have same map type
 * Input:
 * char*
 * Output:
 * 1 - if same map type
 * 0 - otherwise
 */
int selectIfSameMapType(Map*, char*);

/*
 * Function to set if the sorting is done in decreasing order
 * Input:
 * Map*
 * Map*        elements that we compare
 * Output:
 * 1 if first > second
 * 0 otherwise
 */
int reverseSorting(Map*, Map*);

/*
 * Function to set if the sorting is done in increasing order
 * Input:
 * Map*
 * Map*        elements that we compare
 * Output:
 * 1 if first < second
 * 0 otherwise
 */
int normalSorting(Map* , Map*);

/*
 * Function to filter maps that are subtype of given map type
 * Input:
 * char* - map type
 * Map* - map
 * Output:
 * 1 - if subtype of given map
 * 0 - otherwise
 */
int selectIfMapTypeIsSubTypeOfGivenType(Map* , char*);

/*
 * Function to list all files
 * Input:
 * char*, Map*
 * Output: 1
 */
int selectAllForAmbiguity(Map*, char*);