//
// Created by Octavian Custura on 18/03/2020.
//

#include "DynamicArray.h"
#include "Footage.h"
#include <exception>
#include <string>

template<class TypeOfElement>
DynamicArray<TypeOfElement>::DynamicArray(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->elements = new TypeOfElement[this->capacity];
}

template<class TypeOfElement>
DynamicArray<TypeOfElement>::~DynamicArray() {
    delete [] this->elements;
    this->size = 0;
}

template<class TypeOfElement>
void DynamicArray<TypeOfElement>::addElement(TypeOfElement newElement) {
    if (size == capacity) {
        resizeArray(2 * capacity);
    }
    elements[size++] = newElement;
}

template<class TypeOfElement>
void DynamicArray<TypeOfElement>::resizeArray(int newCapacity) {
    capacity = newCapacity;
    auto * auxiliaryArray = new TypeOfElement[capacity];
    for (int i = 0; i < size; ++i) {
        auxiliaryArray[i] = elements[i];
    }
    delete [] elements;
    elements = auxiliaryArray;
}

template<class TypeOfElement>
void DynamicArray<TypeOfElement>::addElementToPosition(TypeOfElement newElement, int position) {
    if (position > size or position < 0) {
        throw std::exception();
    }
    if (size == capacity) {
        resizeArray(2 * capacity);
    }
    size++;
    for (int i = size; i > position; ++i) {
        elements[i] = elements[i - 1];
    }
    elements[position] = newElement;
}

template<class TypeOfElement>
void DynamicArray<TypeOfElement>::setElement(TypeOfElement newElement, int position) {
    if (position >= size or position < 0) {
        throw std::exception();
    }
    elements[position] = newElement;
}

template<class TypeOfElement>
void DynamicArray<TypeOfElement>::removeElementFromPosition(int position) {
    if (position >= size or position < 0) {
        throw std::exception();
    }
    if (size == capacity / 4) {
        resizeArray(capacity / 2);
    }
    size--;
    for (int i = position; i < size; ++i) {
        elements[i] = elements[i + 1];
    }
}

template<class TypeOfElement>
TypeOfElement DynamicArray<TypeOfElement>::getElement(int position) {
    if (position >= size or position < 0) {
        throw std::exception();
    }
    return elements[position];
}

template<class TypeOfElement>
int DynamicArray<TypeOfElement>::getSize() const {
    return size;
}

template<class TypeOfElement>
DynamicArray<TypeOfElement>::DynamicArray(const DynamicArray &copyArray) {
    size = copyArray.size;
    capacity = copyArray.capacity;
    elements = new TypeOfElement[capacity];
    for (int i = 0; i < size; ++i) {
        elements[i] = copyArray.elements[i];
    }
}

template<class TypeOfElement>
DynamicArray<TypeOfElement>& DynamicArray<TypeOfElement>::operator=(const DynamicArray<TypeOfElement> &copyArray) {
    if (this == &copyArray) {
        return *this;
    }
    size = copyArray.size;
    capacity = copyArray.capacity;

    delete [] elements;
    elements = new TypeOfElement[this->capacity];
    for (int i = 0; i < size; ++i) {
        elements[i] = copyArray.elements[i];
    }
    return *this;
}

template class DynamicArray<Footage>;
