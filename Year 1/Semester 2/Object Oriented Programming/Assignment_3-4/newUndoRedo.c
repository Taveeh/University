//
// Created by Octavian Custura on 25/03/2020.
//

#include "newUndoRedo.h"
#include <stdlib.h>

UndoRedoNew *createUndoRedoNew() {
    UndoRedoNew* result = (UndoRedoNew*)malloc(sizeof(UndoRedoNew));
    result->current = 0;
    result->maximum = 0;
    result->undoRedo = createDynamicArray(5, &destroyDynamicArray, &copyDynamicArray);
    return result;
}

void addUndoNew(UndoRedoNew *undoRedoNew, DynamicArray *dynamicArray) {
    clearRedoNew(undoRedoNew);
    addElementToDynamicArray(undoRedoNew->undoRedo, dynamicArray);
    undoRedoNew->maximum += 1;
    undoRedoNew->current += 1;
}

void clearRedoNew(UndoRedoNew *undoRedoNew) {
    for (int i = undoRedoNew->maximum - 1; i > undoRedoNew->current; --i) {
        destroyDynamicArray(getElementOnPosition(undoRedoNew->undoRedo, i));
    }
    undoRedoNew->maximum = undoRedoNew->current;
}

DynamicArray *undoFunction(UndoRedoNew *undoRedoNew) {
    if (undoRedoNew->current == 0) {
        return NULL;
    }
    if (firstCall(undoRedoNew)) {
        --undoRedoNew->current;
        return (DynamicArray*)getElementOnPosition(undoRedoNew->undoRedo, --undoRedoNew->current);
    }
    return (DynamicArray*)getElementOnPosition(undoRedoNew->undoRedo, --undoRedoNew->current);
}

DynamicArray *redoFunction(UndoRedoNew *undoRedoNew) {
    if (undoRedoNew->maximum == undoRedoNew->current) {
        return NULL;
    }
    return (DynamicArray*)getElementOnPosition(undoRedoNew->undoRedo, ++undoRedoNew->current);
}

void destroyNewUndoRedo(UndoRedoNew *undoRedoNew) {
    undoRedoNew->maximum--;
    for (int i = 0; i < undoRedoNew->maximum; ++i) {
        undoRedoNew->undoRedo->destroyElementFunction(getElementOnPosition(undoRedoNew->undoRedo, i));
    }
    free(undoRedoNew);
}

int firstCall(UndoRedoNew* undoRedoNew) {
    return undoRedoNew->maximum == undoRedoNew->current;
}





