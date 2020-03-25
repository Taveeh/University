//
// Created by Octavian Custura on 25/03/2020.
//

#pragma once

#include "dynamicArray.h"

typedef struct {
    DynamicArray* undoRedo;
    int current;
    int maximum;
}UndoRedoNew;

UndoRedoNew* createUndoRedoNew();

void addUndoNew(UndoRedoNew* undoRedoNew, DynamicArray* dynamicArray);

void clearRedoNew(UndoRedoNew* undoRedoNew);

DynamicArray* undoFunction(UndoRedoNew* undoRedoNew);

DynamicArray* redoFunction(UndoRedoNew* undoRedoNew);

int firstCall(UndoRedoNew* undoRedoNew);

void destroyNewUndoRedo(UndoRedoNew* undoRedoNew);
