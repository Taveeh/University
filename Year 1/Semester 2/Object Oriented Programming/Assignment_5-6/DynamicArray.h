//
// Created by Octavian Custura on 18/03/2020.
//

#ifndef ASSIGNMENT_5_6_DYNAMICARRAY_H
#define ASSIGNMENT_5_6_DYNAMICARRAY_H

#include <string>
template <class TypeOfElement>
class DynamicArray {
private:
    int capacity{}, size{};

    TypeOfElement *elements;

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

    ~DynamicArray();

};


#endif //ASSIGNMENT_5_6_DYNAMICARRAY_H
