//
// Created by Octavian Custura on 18/03/2020.
//

#ifndef ASSIGNMENT_5_6_DYNAMICARRAY_H
#define ASSIGNMENT_5_6_DYNAMICARRAY_H

#include <string>
#include <exception>
template <class TypeOfElement>
class DynamicArray {

private:
    int capacity{}, size{};

    TypeOfElement *elements;

    int currentElementIndex;
    void resizeArray(int capacity);


public:

    explicit DynamicArray(int capacity = 10);

    DynamicArray(const DynamicArray& copyArray);

    DynamicArray& operator=(const DynamicArray& copyArray);

    void addElement(TypeOfElement newElement);

    void addElementToPosition(TypeOfElement newElement, int position);

    void removeElementFromPosition(int position);

    TypeOfElement getElement(int position);

    void setElement(TypeOfElement newElement, int position);

    [[nodiscard]] int getSize() const;

    TypeOfElement getCurrentElement();

    ~DynamicArray();

};


template <class TypeOfElement>
TypeOfElement DynamicArray<TypeOfElement>::getCurrentElement()  {
    if (currentElementIndex == size) {
        currentElementIndex = 0;
    }
    return elements[currentElementIndex++];
}

template<class TypeOfElement>
DynamicArray<TypeOfElement>::DynamicArray(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->elements = new TypeOfElement[this->capacity];
    this->currentElementIndex = 0;
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

    for (int i = size; i > position; ++i) {
        elements[i] = elements[i - 1];
    }
    size++;
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
    currentElementIndex = copyArray.currentElementIndex;
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


#endif //ASSIGNMENT_5_6_DYNAMICARRAY_H
