//
// Created by Octavian Custura on 16/03/2020.
//

#pragma once

#include "domain.h"
#define FIRST_CAPACITY 5

typedef void* TypeOfElement;

typedef void (*DestroyElementFunctionType)(void*);

typedef TypeOfElement (*copyElementFunctionType)(TypeOfElement);

typedef struct {
    TypeOfElement* dynamicArrayElements;
    int numberOfElements;
    int capacityOfDynamicArray;
    DestroyElementFunctionType destroyElementFunction;
    copyElementFunctionType copyElementFunction;
} DynamicArray;

/*
 * Function to delete an element from a given position in dynamic array
 * Input:
 * DynamicArray* - dynamic array
 * int - position
 * Output:
 * 1 - if element was deleted
 * 0 - otherwise
 */
int deleteElementFromPosition(DynamicArray *dynamicArray, int position);

/*
 * Constructor
 */
DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElementFunction, copyElementFunctionType copyElementFunction);

/*
 * Destructor
 */
void destroyDynamicArray(DynamicArray* dynamicArray);

DynamicArray *copyDynamicArray(DynamicArray* dynamicArray);
/*
 * Resize dynamic array
 * Input:
 * DynamicArray* - dynamic array
 * int - new capacity of array
 * Output:
 * 1 - if resize was done
 * 0 - otherwise
 */
int resizeDynamicArray(DynamicArray* dynamicArray, int newCapacity);

/*
 * Add element to the end of Dynamic Array
 * Input:
 * DynamicArray* - dynamic array
 * TypeOfElement - element to be added
 * Output:
 * 1 - if added
 * 0 - otherwise
 */
int addElementToDynamicArray(DynamicArray* dynamicArray, TypeOfElement elementToBeAdded);

/*
 * Get the length of the array
 * Input:
 * DynamicArray*
 * Output:
 * int - length
 */
int getLengthOfDynamicArray(DynamicArray* dynamicArray);

/*
 * Get the element on given position
 * Input:
 * DynamicArray*
 * int - position
 * Output:
 * TypeOfElement - the element on position
 */
TypeOfElement getElementOnPosition(DynamicArray* dynamicArray, int position);

/*
 * Insert element on given position
 * Input:
 * DynamicArray*
 * int - position
 * TypeOfElement - element to be added
 * Output:
 * 1 - if added
 * 0 - otherwise
 */
int insertElementToPosition(DynamicArray* dynamicArray, int position, TypeOfElement elementToBeAdded);

