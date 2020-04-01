//
// Created by Octavian Custura on 16/03/2020.
//

#include "dynamicArray.h"
#include <stdlib.h>

DynamicArray *createDynamicArray(int capacity, DestroyElementFunctionType destroyElementFunction, copyElementFunctionType copyElementFunction) {
    DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (dynamicArray == NULL) {
        return NULL;
    }
    dynamicArray->capacityOfDynamicArray = capacity;
    dynamicArray->numberOfElements = 0;
    dynamicArray->dynamicArrayElements = (TypeOfElement*)malloc(sizeof(TypeOfElement) * capacity);
    if (dynamicArray->dynamicArrayElements == NULL) {
        return NULL;
    }
    dynamicArray->destroyElementFunction = destroyElementFunction;
    dynamicArray->copyElementFunction = copyElementFunction;
    return dynamicArray;
}

void destroyDynamicArray(DynamicArray *dynamicArray) {
    if (dynamicArray == NULL) {
        return;
    }
    for (int dynamicArrayElementIndex = 0;
         dynamicArrayElementIndex < dynamicArray->numberOfElements; ++dynamicArrayElementIndex) {
        if (dynamicArray->dynamicArrayElements[dynamicArrayElementIndex] != NULL) {
            dynamicArray->destroyElementFunction(dynamicArray->dynamicArrayElements[dynamicArrayElementIndex]);
        }
    }
    free(dynamicArray->dynamicArrayElements);
    dynamicArray->dynamicArrayElements = NULL;
    free(dynamicArray);
}

int resizeDynamicArray(DynamicArray *dynamicArray, int newCapacity) {
    if (dynamicArray == NULL) {
        return -1;
    }
    dynamicArray->capacityOfDynamicArray = newCapacity;
    TypeOfElement *auxiliaryArrayOfMaps = (TypeOfElement *)realloc(dynamicArray->dynamicArrayElements, dynamicArray->capacityOfDynamicArray * sizeof(TypeOfElement));
    if (auxiliaryArrayOfMaps == NULL) {
        return -1;
    }
    dynamicArray->dynamicArrayElements = auxiliaryArrayOfMaps;
    return 0;
}

int addElementToDynamicArray(DynamicArray *dynamicArray, TypeOfElement elementToBeAdded) {
    if (dynamicArray->numberOfElements == dynamicArray->capacityOfDynamicArray) {
        resizeDynamicArray(dynamicArray, 2 * dynamicArray->capacityOfDynamicArray);
    }
    dynamicArray->dynamicArrayElements[dynamicArray->numberOfElements++] = elementToBeAdded;
    return 1;
}

int deleteElementFromPosition(DynamicArray *dynamicArray, int position) {
    if (position >= dynamicArray->numberOfElements) {
        return 0;
    }
    if (dynamicArray->numberOfElements == dynamicArray->capacityOfDynamicArray / 4) {
        resizeDynamicArray(dynamicArray, dynamicArray->capacityOfDynamicArray / 2);
    }
    destroyMap(dynamicArray->dynamicArrayElements[position]);
    for (int indexRemoveElement = position; indexRemoveElement < dynamicArray->numberOfElements - 1; ++indexRemoveElement) {
        dynamicArray->dynamicArrayElements[indexRemoveElement] = dynamicArray->dynamicArrayElements[indexRemoveElement + 1];
    }
    dynamicArray->numberOfElements--;
    return 1;
}

int getLengthOfDynamicArray(DynamicArray *dynamicArray) {
    return dynamicArray->numberOfElements;
}

TypeOfElement getElementOnPosition(DynamicArray *dynamicArray, int position) {
    if (position >= dynamicArray->numberOfElements) {
        return NULL;
    }
    return dynamicArray->dynamicArrayElements[position];
}

int insertElementToPosition(DynamicArray *dynamicArray, int position, TypeOfElement elementToBeAdded) {
    if (position > dynamicArray->numberOfElements) {
        return 0;
    }
    if (dynamicArray->numberOfElements == dynamicArray->capacityOfDynamicArray) {
        resizeDynamicArray(dynamicArray, 2 * dynamicArray->capacityOfDynamicArray);
    }
    for (int i = dynamicArray->numberOfElements; i > position; --i) {
        dynamicArray->dynamicArrayElements[i] = dynamicArray->dynamicArrayElements[i - 1];
    }
    dynamicArray->dynamicArrayElements[position] = elementToBeAdded;
    dynamicArray->numberOfElements++;
    return 1;
}

DynamicArray *copyDynamicArray(DynamicArray *dynamicArray) {
    DynamicArray *result = (DynamicArray*)malloc(sizeof(DynamicArray));
    result->capacityOfDynamicArray = dynamicArray->capacityOfDynamicArray;
    result->numberOfElements = dynamicArray->numberOfElements;
    result->dynamicArrayElements = (TypeOfElement*)malloc(result->capacityOfDynamicArray * sizeof(TypeOfElement));
    result->copyElementFunction = dynamicArray->copyElementFunction;
    for (int i = 0; i < dynamicArray->numberOfElements; ++i) {
        result->dynamicArrayElements[i] = result->copyElementFunction(dynamicArray->dynamicArrayElements[i]);
    }
    result->destroyElementFunction = dynamicArray->destroyElementFunction;
    return result;
}
