//
// Created by Octavian Custura on 16/03/2020.
//

#include "testDynamicArray.h"
#include <stdlib.h>
#include <assert.h>

void test_createDynamicArray_ValidInput_CreateDynamicArrayGivenCapacity() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, &copyMap);
    if (dynamicArray == NULL) {
        assert(0);
    }
    assert(1);
    assert(dynamicArray->capacityOfDynamicArray == 2);
    assert(dynamicArray->numberOfElements == 0);
    destroyDynamicArray(dynamicArray);
}

void test_addElementToDynamicArray_ValidMap_MapAddedToArray() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, &copyMap);
    Map* map = createMap(123, "abc", "def", 456);
    assert(addElementToDynamicArray(dynamicArray, map) == 1);
    assert(getLengthOfDynamicArray(dynamicArray) == 1);
    destroyDynamicArray(dynamicArray);
}

void test_addElementToDynamicArray_ManyElements_CapacityDoubles() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, copyMap);
    Map* map1 = createMap(123, "abc", "def", 456);
    assert(addElementToDynamicArray(dynamicArray, map1) == 1);
    Map* map2 = createMap(124, "asa", "si asa", 32144);
    assert(addElementToDynamicArray(dynamicArray, map2) == 1);
    Map* map3 = createMap(125, "sdfa", "afasfd", 3412);
    assert(addElementToDynamicArray(dynamicArray, map3) == 1);
    assert(getLengthOfDynamicArray(dynamicArray) == 3);
    assert(dynamicArray->capacityOfDynamicArray == 4);
    destroyDynamicArray(dynamicArray);
}

void test_getElementOnPosition_ValidInput_GetAMap() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, copyMap);
    Map* map1 = createMap(123, "abc", "def", 456);
    assert(addElementToDynamicArray(dynamicArray, map1) == 1);
    assert(getElementOnPosition(dynamicArray, 0) == map1);
    destroyDynamicArray(dynamicArray);
}

void test_getElementOnPosition_InvalidInput_GetNULL() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, copyMap);
    Map* map1 = createMap(123, "abc", "def", 456);
    assert(addElementToDynamicArray(dynamicArray, map1) == 1);
    assert(getElementOnPosition(dynamicArray, 2) == NULL);
    destroyDynamicArray(dynamicArray);
}

void test_deleteElementFromPosition_ValidInput_ElementRemoved() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, copyMap);
    Map* map = createMap(123, "abc", "def", 456);
    assert(addElementToDynamicArray(dynamicArray, map) == 1);
    assert(deleteElementFromPosition(dynamicArray, 0) == 1);
    destroyDynamicArray(dynamicArray);
}


void test_deleteElementFromPosition_RemovedTooManyItems_CapacityBecomesSmaller() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, copyMap);
    Map* map1 = createMap(123, "abc", "def", 456);
    assert(addElementToDynamicArray(dynamicArray, map1) == 1);
    Map* map2 = createMap(124, "asa", "si asa", 32144);
    assert(addElementToDynamicArray(dynamicArray, map2) == 1);
    Map* map3 = createMap(125, "sdfa", "afasfd", 3412);
    assert(addElementToDynamicArray(dynamicArray, map3) == 1);
    assert(dynamicArray->capacityOfDynamicArray == 4);
    assert(deleteElementFromPosition(dynamicArray, 0) == 1);
    assert(deleteElementFromPosition(dynamicArray, 0) == 1);
    assert(deleteElementFromPosition(dynamicArray, 0) == 1);
    assert(dynamicArray->capacityOfDynamicArray == 2);
    destroyDynamicArray(dynamicArray);
}

void testAllDynamicArray() {
     test_createDynamicArray_ValidInput_CreateDynamicArrayGivenCapacity();

     test_addElementToDynamicArray_ValidMap_MapAddedToArray();

     test_addElementToDynamicArray_ManyElements_CapacityDoubles();

     test_getElementOnPosition_ValidInput_GetAMap();

     test_getElementOnPosition_InvalidInput_GetNULL();

    test_deleteElementFromPosition_RemovedTooManyItems_CapacityBecomesSmaller();

    test_deleteElementFromPosition_ValidInput_ElementRemoved();

    test_insertElementToPosition_ValidPosition_ElementAdded();

    test_insertElementToPosition_InvalidPosition_ElementNotAdded();
}

void test_insertElementToPosition_ValidPosition_ElementAdded() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, copyMap);
    Map* map1 = createMap(123, "abc", "def", 456);
    assert(insertElementToPosition(dynamicArray, 0, map1) == 1);
    destroyDynamicArray(dynamicArray);
}

void test_insertElementToPosition_InvalidPosition_ElementNotAdded() {
    DynamicArray* dynamicArray = createDynamicArray(2, &destroyMap, copyMap);
    Map* map1 = createMap(123, "abc", "def", 456);
    assert(insertElementToPosition(dynamicArray, 1, map1) == 0);
    destroyMap(map1);
    destroyDynamicArray(dynamicArray);
}



