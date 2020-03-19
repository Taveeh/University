//
// Created by Octavian Custura on 16/03/2020.
//

#ifndef ASSIGNMENT_3_TESTDYNAMICARRAY_H
#define ASSIGNMENT_3_TESTDYNAMICARRAY_H

#include "dynamicArray.h"

void test_createDynamicArray_ValidInput_CreateDynamicArrayGivenCapacity();

void test_addElementToDynamicArray_ValidMap_MapAddedToArray();

void test_addElementToDynamicArray_ManyElements_CapacityDoubles();

void test_getElementOnPosition_ValidInput_GetAMap();

void test_getElementOnPosition_InvalidInput_GetNULL();

void test_deleteElementFromPosition_ValidInput_ElementRemoved();

void test_deleteElementFromPosition_RemovedTooManyItems_CapacityBecomesSmaller();

void test_insertElementToPosition_ValidPosition_ElementAdded();

void test_insertElementToPosition_InvalidPosition_ElementNotAdded();
void testAllDynamicArray();
#endif //ASSIGNMENT_3_TESTDYNAMICARRAY_H
