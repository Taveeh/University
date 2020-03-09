//
// Created by Octavian Custura on 04/03/2020.
//

#pragma once

#include "domain.h"

typedef struct {
    Map listOfMaps[100];
    int numberOfMaps;
} Repository;

Repository createRepository();

int addMapToRepository(Repository* repository, Map map);

int updateMapFromRepository(Repository* repository, Map* map);

int deleteMapFromRepository(Repository* repository, int mapCatalogueNumber);

int searchMapInRepository(Repository* repository, int mapCatalogueNumber);

void testRepository();
