//
// Created by Octavian Custura on 16/03/2020.
//

#ifndef ASSIGNMENT_3_TESTREPOSITORY_H
#define ASSIGNMENT_3_TESTREPOSITORY_H

#include "repository.h"

void testAllRepository();

void test_searchMapInRepositoryByID_ValidID_ReturnPosition();

void test_searchMapInRepositoryByID_InvalidID_MinusOne();

void test_addMapToRepository_ValidID_MapAdded();

void test_addMapToRepository_Duplicate_MapNotAdded();

void test_updateMapFromRepository_ValidID_MapUpdated();

void test_updateMapFromRepository_InvalidID_MapNotUpdated();

void test_deleteMapFromRepository_ValidID_MapRemoved();

void test_deleteMapFromRepository_InvalidID_MapNotRemoved();


#endif //ASSIGNMENT_3_TESTREPOSITORY_H
