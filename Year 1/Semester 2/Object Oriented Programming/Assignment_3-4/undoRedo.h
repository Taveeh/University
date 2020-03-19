//
// Created by Octavian Custura on 17/03/2020.
//

#pragma once

#include "dynamicArray.h"
#define INITIAL_CAPACITY 10
typedef struct {
    Map* map;
    char* typeOfOperation;
}Operation;

typedef struct {
    int undoSize;
    int undoCapacity;
    Operation** undoList;
    int flag;
    int redoSize;
    int redoCapacity;
    Operation** redoList;
}UndoRedo;

/*
 * Constructor Operation
 */
Operation* createOperation(Map* map, char* typeOfOperation);

/*
 * Get type of operation
 * Input:
 * Operation*
 * Output:
 * char*
 */
char* getOperationType(Operation* operation);

/*
 * Get Map of an operation
 * Input:
 * Operation* operation
 * Output:
 * Map*
 */
Map* getMapFromOperation(Operation* operation);

/*
 * Destructor Operation
 */
void destroyOperation(Operation* operation);

/*
 * Constructor UndoRedo
 */
UndoRedo* createUndoRedo();

/*
 * Destructor UndoRedo
 */
void destroyUndoRedo(UndoRedo* undoRedo);

/*
 * Prepares the undo of an add operation
 * Input:
 * UndoRedo*
 * Map*
 */
void addUndo(UndoRedo* undoRedo, Map* mapToBeAdded);

/*
 * Prepares the redo of an add operation
 * Input:
 * UndoRedo*
 * Map*
 */
void addRedo(UndoRedo* undoRedo, Map *mapToBeAdded);

/*
 * Resizes undo list
 * Input:
 * UndoRedo*
 */
void resizeUndo(UndoRedo* undoRedo);

/*
 * Resizes redo list
 * Input:
 * UndoRedo*
 */
void resizeRedo(UndoRedo* undoRedo);

/*
 * Clears redo list
 * Input:
 * UndoRedo*
 */
void clearRedo(UndoRedo* undoRedo);

/*
 * Prepares the redo of an update operation
 * Input:
 * UndoRedo*
 * Map*
 */
void updateRedo(UndoRedo* undoRedo, Map* mapToBeEdited);

/*
 * Prepares the undo of an update operation
 * Input:
 * UndoRedo*
 * Map*
 */
void updateUndo(UndoRedo* undoRedo, Map* mapToBeEdited);

/*
 * Prepares the undo of a delete operation
 * Input:
 * UndoRedo*
 * Map*
 */
void deleteUndo(UndoRedo* undoRedo, Map* mapToBeRemoved);

/*
 * Prepares the redo of a delete operation
 * Input:
 * UndoRedo*
 * Map*
 */
void deleteRedo(UndoRedo* undoRedo, Map* mapToBeRemoved);

/*
 * Get the next undo to be done
 * Input:
 * UndoRedo*
 */
Operation* getLastUndo(UndoRedo* undoRedo);

/*
 * Get the next redo to be done
 * Input:
 * UndoRedo*
 */
Operation* getLastRedo(UndoRedo* undoRedo);

/*
 * Changes flag that shows if the operation is from undo/redo or not
 * Input:
 * UndoRedo*
 * int - new value of flag
 */
void changeFlag(UndoRedo* undoRedo, int value);

/*
 * Returns the flag of the UndoRedo
 * Input:
 * UndoRedo*
 * Output:
 * int - flag
 */
int getFlag(UndoRedo* undoRedo);