//
// Created by Octavian Custura on 16/03/2020.
//

#include "testDomain.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_getCatalogueNumber_ValidInput_UnsignedInt() {
    Map* map = createMap(123, "abc", "def", 456);
    assert(getCatalogueNumber(map) == 123);
    destroyMap(map);
}

void test_getCatalogueNumber_InvalidInput_MinusOne() {
    Map* map;
    map = NULL;
    assert(getCatalogueNumber(map) == -1);
    free(map);
}

void test_getYearsOfStorage_ValidInput_UnsignedInt() {
    Map* map = createMap(123, "abc", "def", 456);
    assert(getYearsOfStorage(map) == 456);
    destroyMap(map);
}

void test_getYearsOfStorage_InvalidInput_MinusOne() {
    Map* map;
    map = NULL;
    assert(getYearsOfStorage(map) == -1);
    free(map);
}

void test_getStateOfDeterioration_ValidInput_CharPointer() {
    Map* map = createMap(123, "abc", "def", 456);
    assert(strcmp(getStateOfDeterioration(map), "abc") == 0);
    destroyMap(map);
}

void test_getStateOfDeterioration_InvalidInput_NULL() {
    Map* map;
    map = NULL;
    assert(getStateOfDeterioration(map) == NULL);
    free(map);
}

void test_getMapType_ValidInput_CharPointer() {
    Map* map = createMap(123, "abc", "def", 456);
    assert(strcmp(getMapType(map), "def") == 0);
    destroyMap(map);
}

void test_getMapType_InvalidInput_NULL() {
    Map* map;
    map = NULL;
    assert(getMapType(map) == NULL);
    free(map);
}

void test_changeStateOfDeterioration_ValidInput_StateOfDeteriorationModified() {
    Map* map = createMap(123, "abc", "def", 456);
    changeStateOfDeterioration(map, "abd");
    assert(strcmp(getStateOfDeterioration(map), "abd") == 0);
    destroyMap(map);
}

void test_changeStateOfDeterioration_InvalidInput_StateOfDeteriorationNotModified() {
    Map* map = createMap(123, "abc", "def", 456);
    char* stateOfDeterioration = (char*)malloc(sizeof(char));
    strcpy(stateOfDeterioration, "");
    changeStateOfDeterioration(map, stateOfDeterioration);
    assert(strcmp(getStateOfDeterioration(map), stateOfDeterioration) != 0);
    free(stateOfDeterioration);
    destroyMap(map);
}

void test_changeMapType_ValidInput_MapTypeModified() {
    Map* map = createMap(123, "abc", "def", 456);
    changeMapType(map, "abd");
    assert(strcmp(getMapType(map), "abd") == 0);
    destroyMap(map);
}

void test_changeMapType_InvalidInput_MapTypeNotModified() {
    Map* map = createMap(123, "abc", "def", 456);
    char* mapType = (char*)malloc(sizeof(char));
    strcpy(mapType, "");
    changeMapType(map, mapType);
    assert(strcmp(getMapType(map), mapType) != 0);
    free(mapType);
    destroyMap(map);
}

void test_changeYearsOfStorage_ValidInput_YearsOfStorageModified() {
    Map* map = createMap(123, "abc", "def", 456);
    changeYearsOfStorage(map, 7);
    assert(getYearsOfStorage(map) == 7);
    destroyMap(map);
}

void test_changeYearsOfStorage_InvalidInput_YearsOfStorageNotModified() {
    Map* map = createMap(123, "abc", "def", 456);
    changeYearsOfStorage(map, -1);
    assert(getYearsOfStorage(map) != -1);
    assert(getYearsOfStorage(map) == 456);
    destroyMap(map);
}

void testAllDomain() {
    test_getCatalogueNumber_ValidInput_UnsignedInt();

    test_getCatalogueNumber_InvalidInput_MinusOne();

    test_getYearsOfStorage_ValidInput_UnsignedInt();

    test_getYearsOfStorage_InvalidInput_MinusOne();

    test_getStateOfDeterioration_ValidInput_CharPointer();

    test_getStateOfDeterioration_InvalidInput_NULL();

    test_getMapType_ValidInput_CharPointer();

    test_getMapType_InvalidInput_NULL();

    test_changeStateOfDeterioration_ValidInput_StateOfDeteriorationModified();

    test_changeStateOfDeterioration_InvalidInput_StateOfDeteriorationNotModified();

    test_changeMapType_ValidInput_MapTypeModified();

    test_changeMapType_InvalidInput_MapTypeNotModified();

    test_changeYearsOfStorage_ValidInput_YearsOfStorageModified();

    test_changeYearsOfStorage_InvalidInput_YearsOfStorageNotModified();

}















