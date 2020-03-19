//
// Created by Octavian Custura on 17/03/2020.
//

#include "undoRedo.h"
#include <stdlib.h>
#include <string.h>

Operation *createOperation(Map *map, char *typeOfOperation) {
    Operation* result = (Operation*)malloc(sizeof(Operation));
    char* newStateOfDeterioration = (char*)malloc(sizeof(char) * strlen(getStateOfDeterioration(map)) + 1);
    char* newMapType = (char*)malloc(sizeof(char) * strlen(getMapType(map)) + 1 );
    strcpy(newStateOfDeterioration, getStateOfDeterioration(map));
    strcpy(newMapType, getMapType(map));
    result->map = createMap(getCatalogueNumber(map), newStateOfDeterioration, newMapType, getYearsOfStorage(map));
    result->typeOfOperation = (char*)malloc(sizeof(char) * (strlen(typeOfOperation) + 1));
    strcpy(result->typeOfOperation, typeOfOperation);
    free(newStateOfDeterioration);
    free(newMapType);
    return result;
}

char *getOperationType(Operation *operation) {
    return operation->typeOfOperation;
}

Map *getMapFromOperation(Operation *operation) {
    return operation->map;
}

void destroyOperation(Operation *operation) {
    free(operation->typeOfOperation);
    operation->typeOfOperation = NULL;
    destroyMap(operation->map);
    free(operation);
}

UndoRedo *createUndoRedo() {
    UndoRedo* result = (UndoRedo*)malloc(sizeof(UndoRedo));
    result->undoSize = 0;
    result->redoSize = 0;
    result->undoCapacity = INITIAL_CAPACITY;
    result->redoCapacity = INITIAL_CAPACITY;
    result->redoList = (Operation**)malloc(sizeof(Operation*) * result->redoCapacity);
    result->undoList = (Operation**)malloc(sizeof(Operation*) * result->undoCapacity);
    result->flag = 0;
    return result;
}

void resizeUndo(UndoRedo *undoRedo) {
    if (undoRedo == NULL) {
        return;
    }
    undoRedo->undoCapacity *= 2;
    Operation** auxiliarySpace = realloc(undoRedo->undoList, undoRedo->undoCapacity * sizeof(Operation*));
    if (auxiliarySpace == NULL) {
        return;
    }
    undoRedo->undoList = auxiliarySpace;
}

void resizeRedo(UndoRedo *undoRedo) {
        if (undoRedo == NULL) {
            return;
        }
        undoRedo->redoCapacity *= 2;
        Operation** auxiliarySpace = realloc(undoRedo->redoList, undoRedo->redoCapacity * sizeof(Operation*));
        if (auxiliarySpace == NULL) {
            return;
        }
        undoRedo->redoList = auxiliarySpace;
}

void addUndo(UndoRedo* undoRedo, Map* mapToBeAdded) {
    if (undoRedo->undoCapacity == undoRedo->undoSize) {
        resizeUndo(undoRedo);
    }
    undoRedo->undoList[undoRedo->undoSize++] = createOperation(mapToBeAdded, "delete");
}

void addRedo(UndoRedo *undoRedo, Map *mapToBeAdded) {
    if (undoRedo->redoCapacity == undoRedo->redoSize) {
        resizeRedo(undoRedo);
    }
    undoRedo->redoList[undoRedo->redoSize++] = createOperation(mapToBeAdded, "add");
}

void clearRedo(UndoRedo *undoRedo) {
    for (int redoIndex = 0; redoIndex < undoRedo->redoSize; ++redoIndex) {
        destroyOperation(undoRedo->redoList[redoIndex]);
    }
    undoRedo->redoSize = 0;
}


void updateUndo(UndoRedo *undoRedo, Map *mapToBeEdited) {
    if (undoRedo->undoSize == undoRedo->undoCapacity) {
        resizeUndo(undoRedo);
    }
    undoRedo->undoList[undoRedo->undoSize++] = createOperation(mapToBeEdited, "update");
}


void updateRedo(UndoRedo *undoRedo, Map *mapToBeEdited) {
    if (undoRedo->redoSize == undoRedo->redoCapacity) {
        resizeRedo(undoRedo);
    }
    undoRedo->redoList[undoRedo->redoSize++] = createOperation(mapToBeEdited, "update");
}

void deleteUndo(UndoRedo *undoRedo, Map *mapToBeRemoved) {
    if (undoRedo->undoSize == undoRedo->undoCapacity) {
        resizeUndo(undoRedo);
    }
    undoRedo->undoList[undoRedo->undoSize++] = createOperation(mapToBeRemoved, "add");
}

void deleteRedo(UndoRedo *undoRedo, Map *mapToBeRemoved) {
    if (undoRedo->redoSize == undoRedo->redoCapacity) {
        resizeRedo(undoRedo);
    }
    undoRedo->redoList[undoRedo->redoSize++] = createOperation(mapToBeRemoved, "delete");
}

void destroyUndoRedo(UndoRedo *undoRedo) {
    for (int undoIndex = 0; undoIndex < undoRedo->undoSize; ++undoIndex) {
        destroyOperation(undoRedo->undoList[undoIndex]);
    }
    free(undoRedo->undoList);
    clearRedo(undoRedo);
    free(undoRedo->redoList);
    free(undoRedo);
}

Operation* getLastUndo(UndoRedo *undoRedo) {
    if (undoRedo->undoSize < 1) {
        return NULL;
    }
    return undoRedo->undoList[undoRedo->undoSize - 1];
}

Operation *getLastRedo(UndoRedo *undoRedo) {
    if (undoRedo->redoSize < 1) {
        return NULL;
    }
    return undoRedo->redoList[undoRedo->redoSize - 1];
}

void changeFlag(UndoRedo *undoRedo, int value) {
    undoRedo->flag = value;
}

int getFlag(UndoRedo *undoRedo) {
    return undoRedo->flag;
}


