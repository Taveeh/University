//
// Created by Octavian Custura on 04/03/2020.
//

#include "repository.h"
#include <assert.h>
#include <stdio.h>


int searchMapInRepository(Repository *repository, int mapCatalogueNumber) {
    for (int indexMaps = 0; indexMaps < repository->numberOfMaps; ++indexMaps) {
        if (repository->listOfMaps[indexMaps].mapCatalogueNumber == mapCatalogueNumber) {
            return indexMaps;
        }
    }
    return -1;
}

int addMapToRepository(Repository *repository, Map map) {
    int indexMap = searchMapInRepository(repository, map.mapCatalogueNumber);
    if (indexMap != -1) {
        return 0;
    }
    repository->listOfMaps[repository->numberOfMaps] = map;
    repository->numberOfMaps++;
    return 1;
}

int updateMapFromRepository(Repository *repository, Map* map) {
    int indexMap = searchMapInRepository(repository, map->mapCatalogueNumber);
    if (indexMap == -1) {
        return 0;
    }
    repository->listOfMaps[indexMap] = *map;
    return 1;
}

int deleteMapFromRepository(Repository *repository, int mapCatalogueNumber) {
    int indexMap = searchMapInRepository(repository, mapCatalogueNumber);
    if (indexMap == -1) {
        return 0;
    }
    for (int i = indexMap; i < repository->numberOfMaps - 1; ++i) {
        repository->listOfMaps[i] = repository->listOfMaps[i + 1];
    }
    repository->numberOfMaps--;
    return 1;
}

Repository createRepository() {
    Repository result;
    result.numberOfMaps = 0;
    return result;
}

void testRepository() {
//    printf("Test Repository Start\n");
    Repository repository = createRepository();
    Map testMap = createMap(123, "abc", "def", 456);
    assert(addMapToRepository(&repository, testMap) == 1);
    assert(searchMapInRepository(&repository, 123) == 0);
    assert(searchMapInRepository(&repository, 124) == -1);
    assert(addMapToRepository(&repository, testMap) == 0);
    assert(deleteMapFromRepository(&repository, 123) == 1);
    assert(deleteMapFromRepository(&repository, 123) == 0);
//    printf("Test Repository End\n");
}




