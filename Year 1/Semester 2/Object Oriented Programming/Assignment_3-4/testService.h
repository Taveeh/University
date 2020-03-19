//
// Created by Octavian Custura on 17/03/2020.
//

#ifndef ASSIGNMENT_3_TESTSERVICE_H
#define ASSIGNMENT_3_TESTSERVICE_H

#include "service.h"

void testAllService();

void test_addMapService_ValidInput_MapAdded();

void test_addMapService_Duplicate_MapNotAdded();

void test_removeMapService_ValidInput_MapRemoved();

void test_removeMapService_InvalidInput_MapNotRemoved();

void test_updateMapService_ValidInput_MapUpdated();

void test_updateMapService_InvalidInput_MapNotUpdated();

void test_listAllMaps_AnyInput_GetDynamicArrayOfMaps();

void test_listAllMapsByType_ValidInput_GetFilteredList();

void test_listAllMapsByType_InvalidInput_DoNotFilter();

#endif //ASSIGNMENT_3_TESTSERVICE_H
