//
// Created by Octavian Custura on 17/03/2020.
//

#include "testService.h"
#include <assert.h>
#include <stdlib.h>
#include "functionForFilterAndSort.h"

void test_addMapService_ValidInput_MapAdded() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(addMapService(service, 123, "abc", "def", 456) == 1);
    destroyService(service);
}

void test_addMapService_Duplicate_MapNotAdded() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(addMapService(service, 123, "abc", "def", 456) == 1);
    assert(addMapService(service, 123, "dasf", "Sdsa", 1243) == 0);
    destroyService(service);
}

void testAllService() {
    test_addMapService_Duplicate_MapNotAdded();
    test_addMapService_ValidInput_MapAdded();
    test_removeMapService_ValidInput_MapRemoved();
    test_removeMapService_InvalidInput_MapNotRemoved();
    test_updateMapService_ValidInput_MapUpdated();
    test_updateMapService_InvalidInput_MapNotUpdated();
    test_listAllMaps_AnyInput_GetDynamicArrayOfMaps();
    test_listAllMapsByType_ValidInput_GetFilteredList();
    test_listAllMapsByType_InvalidInput_DoNotFilter();
}

void test_removeMapService_ValidInput_MapRemoved() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(addMapService(service, 123, "abc", "def", 456) == 1);
    assert(removeMapService(service, "123") == 1);
    destroyService(service);
}

void test_removeMapService_InvalidInput_MapNotRemoved() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(removeMapService(service, "123") == 0);
    destroyService(service);
}

void test_updateMapService_ValidInput_MapUpdated() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(addMapService(service, 123, "abc", "def", 456) == 1);
    assert(updateMapService(service, 123, "ssad", "sda", 4321) == 1);
    destroyService(service);
}

void test_updateMapService_InvalidInput_MapNotUpdated() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(updateMapService(service, 123, "abc", "def", 456) == 0);
    destroyService(service);
}

void test_listAllMaps_AnyInput_GetDynamicArrayOfMaps() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(addMapService(service, 123, "abc", "def", 456) == 1);
    DynamicArray* testArray = createDynamicArray(2, &destroyMap, &copyMap);
    listAllMaps(service, testArray);
    assert(getLengthOfDynamicArray(testArray) == 1);
    destroyService(service);
    destroyDynamicArray(testArray);
}

void test_listAllMapsByType_ValidInput_GetFilteredList() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(addMapService(service, 123, "abc", "def", 456) == 1);
    assert(addMapService(service, 124, "dasf", "Sdsa", 1243) == 1);
    DynamicArray* testArray = createDynamicArray(2, &destroyMap, &copyMap);
    listAllMapsByType(service, "def", testArray, &selectIfSameMapType);
    assert(getLengthOfDynamicArray(testArray) == 1);
    destroyService(service);
    destroyDynamicArray(testArray);
}

void test_listAllMapsByType_InvalidInput_DoNotFilter() {
    Repository* repository = createRepository();
    Service* service = createService(repository);
    assert(addMapService(service, 123, "abc", "def", 456) == 1);
    assert(addMapService(service, 124, "dasf", "Sdsa", 1243) == 1);
    DynamicArray* testArray = createDynamicArray(2, &destroyMap, &copyMap);
    char* mapTypeTest = NULL;
    listAllMapsByType(service, mapTypeTest, testArray, &selectIfSameMapType);
    assert(getLengthOfDynamicArray(testArray) == 0);
    destroyService(service);
    destroyDynamicArray(testArray);
}
