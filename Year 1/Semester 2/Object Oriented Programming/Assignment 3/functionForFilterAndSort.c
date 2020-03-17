//
// Created by Octavian Custura on 17/03/2020.
//

#include "functionForFilterAndSort.h"
#include <string.h>

int selectIfSameMapType(Map *map, char *mapType) {
    return (strcmp(getMapType(map), mapType) == 0);
}


int selectIfMapTypeIsSubTypeOfGivenType(Map *map, char *mapType) {
    return strstr(getMapType(map), mapType) != NULL;
}

int selectAllForAmbiguity(Map * map, char *mapType) {
    return 1;
}

int reverseSorting(Map* element1, Map* element2) {
    return element1->yearsOfStorage > element2->yearsOfStorage;
}

int normalSorting(Map* element1, Map* element2) {
    return element1->yearsOfStorage < element2->yearsOfStorage;
}
