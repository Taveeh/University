//
// Created by Octavian Custura on 16/03/2020.
//

#include "testRepository.h"
#include "assert.h"
#include <stdio.h>

void testAllRepository() {
    test_searchMapInRepositoryByID_InvalidID_MinusOne();
    test_searchMapInRepositoryByID_ValidID_ReturnPosition();
    test_addMapToRepository_Duplicate_MapNotAdded();
    test_addMapToRepository_ValidID_MapAdded();
    test_updateMapFromRepository_InvalidID_MapNotUpdated();
    test_updateMapFromRepository_ValidID_MapUpdated();
    test_deleteMapFromRepository_InvalidID_MapNotRemoved();
    test_deleteMapFromRepository_ValidID_MapRemoved();
//    test_undoAdd_MapAdded_MapRemoved();
//    test_undoRemove_MapRemoved_MapAdded();
//    test_undoUpdate_MapChanged_MapBack();
}

void test_searchMapInRepositoryByID_InvalidID_MinusOne() {
    Repository* repository = createRepository();
    assert(searchMapInRepositoryByID(repository, 1) == -1);
    destroyRepository(repository);
}

void test_searchMapInRepositoryByID_ValidID_ReturnPosition() {
    Repository* repository = createRepository();
    Map *map = createMap(123, "abc", "def", 456);
    addMapToRepository(repository, map);
    assert(searchMapInRepositoryByID(repository, 123) == 0);
    destroyRepository(repository);
}

void test_addMapToRepository_ValidID_MapAdded() {
    Repository* repository = createRepository();
    Map *map = createMap(123, "abc", "def", 456);
    assert(addMapToRepository(repository, map) == 1);
    destroyRepository(repository);
}

void test_addMapToRepository_Duplicate_MapNotAdded() {
    Repository* repository = createRepository();
    Map *map = createMap(123, "abc", "def", 456);
    assert(addMapToRepository(repository, map) == 1);
    Map *map2 = createMap(123, "sdfafd", "dasf", 1324);
    assert(addMapToRepository(repository, map2) == 0);
    destroyMap(map2);
    destroyRepository(repository);
}

void test_updateMapFromRepository_ValidID_MapUpdated() {
    Repository *repository = createRepository();
    Map *map = createMap(123, "abc", "def", 456);
    addMapToRepository(repository, map);
    Map *map2 = createMap(123, "fdasf", "fdas", 1243);
    assert(updateMapFromRepository(repository, map2) == 1);
    assert(getElementOnPosition(repository->listOfMaps, 0) == map2);
    destroyRepository(repository);
}

void test_updateMapFromRepository_InvalidID_MapNotUpdated() {
    Repository *repository = createRepository();
    Map *map = createMap(123, "abc", "def", 456);
    assert(updateMapFromRepository(repository, map) == 0);
    destroyMap(map);
    destroyRepository(repository);
}

void test_deleteMapFromRepository_ValidID_MapRemoved() {
    Repository *repository = createRepository();
    Map *map = createMap(123, "abc", "def", 456);
    addMapToRepository(repository, map);
    assert(deleteMapFromRepository(repository, 123) == 1);
    destroyRepository(repository);

}

void test_deleteMapFromRepository_InvalidID_MapNotRemoved() {
    Repository *repository = createRepository();
    deleteMapFromRepository(repository, 123);
    destroyRepository(repository);
}
//
//void test_undoAdd_MapAdded_MapRemoved() {
//    Repository* repository = createRepository();
//    Map *map = createMap(123, "abc", "def", 456);
//    addMapToRepository(repository, map);
//    undoRepository(repository);
//    assert(getRepositoryLength(repository) == 0);
//    destroyRepository(repository);
//
//}
//
//void test_undoRemove_MapRemoved_MapAdded() {
//    Repository* repository = createRepository();
//    Map *map = createMap(123, "abc", "def", 456);
//    addMapToRepository(repository, map);
//    deleteMapFromRepository(repository, 123);
//    undoRepository(repository);
//    assert(getRepositoryLength(repository) == 1);
//    destroyRepository(repository);
//}
//
//void test_undoUpdate_MapChanged_MapBack() {
//    Repository* repository = createRepository();
//    Map *map = createMap(123, "abc", "def", 456);
//    addMapToRepository(repository, map);
//    Map *map2 = createMap(123, "bcd", "efg", 5436);
//    updateMapFromRepository(repository, map2);
//    undoRepository(repository);
//    assert(getRepositoryLength(repository) == 1);
//    assert(getYearsOfStorage(getElementOnPosition(repository->listOfMaps, 0)) == 456);
//    destroyRepository(repository);
//}










