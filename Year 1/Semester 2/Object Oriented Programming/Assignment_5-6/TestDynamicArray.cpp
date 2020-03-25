//
// Created by Octavian Custura on 23/03/2020.
//

#include "TestDynamicArray.h"
#include "DynamicArray.h"
#include "Footage.h"
#include <exception>

void TestDynamicArray::test_CopyConstructor_ValidArray_AllAreTheSame() {
    auto dynamicArray1 = DynamicArray<Footage>();
    auto testFootage = Footage();
    dynamicArray1.addElement(testFootage);
    DynamicArray<Footage> dynamicArray2 = DynamicArray(dynamicArray1);
    assert(dynamicArray1.getSize() == 1);
    assert(dynamicArray2.getSize() == 1);
}

void TestDynamicArray::test_all() {
    test_CopyConstructor_ValidArray_AllAreTheSame();
    test_AssignmentOperator_ValidArray_AllAreTheSame();
    test_addElement_ValidElement_ElementAdded();
    test_addElementToPosition_ValidPosition_ElementAdded();
    test_addElementToPosition_NegativePosition_Exception();
    test_removeElementFromPosition_ValidPosition_ElementRemoved();
    test_removeElementFromPosition_NegativePosition_Exception();
    test_setElement_ValidPosition_ElementSet();
    test_setElement_NegativePosition_Exception();
}

void TestDynamicArray::test_AssignmentOperator_ValidArray_AllAreTheSame() {
    auto dynamicArray1 = DynamicArray<Footage>();
    auto testFootage = Footage();
    dynamicArray1.addElement(testFootage);
    DynamicArray<Footage> dynamicArray2, dynamicArray3;
    dynamicArray3 = dynamicArray2 = dynamicArray1;
    assert(dynamicArray3.getSize() == 1);
    assert(dynamicArray2.getSize() == 1);
    assert(dynamicArray1.getSize() == 1);
}

void TestDynamicArray::test_addElement_ValidElement_ElementAdded() {
    auto dynamicArray1 = DynamicArray<Footage>();
    assert(dynamicArray1.getSize() == 0);
    auto testFootage = Footage();
    dynamicArray1.addElement(testFootage);
    assert(dynamicArray1.getSize() == 1);
}

void TestDynamicArray::test_addElementToPosition_ValidPosition_ElementAdded() {
    auto dynamicArray1 = DynamicArray<Footage>();
    assert(dynamicArray1.getSize() == 0);
    auto testFootage = Footage("abc", "def", Date(), 1, "ghi");
    dynamicArray1.addElementToPosition(testFootage, 0);
    assert(dynamicArray1.getElement(0).getTitle() == "abc");
}

void TestDynamicArray::test_addElementToPosition_NegativePosition_Exception() {
    auto dynamicArray1 = DynamicArray<Footage>();
    assert(dynamicArray1.getSize() == 0);
    auto testFootage = Footage();
    try {
        dynamicArray1.addElementToPosition(testFootage, -1);
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
    assert(dynamicArray1.getSize() == 0);
}

void TestDynamicArray::test_removeElementFromPosition_ValidPosition_ElementRemoved() {
    auto dynamicArray1 = DynamicArray<Footage>();
    assert(dynamicArray1.getSize() == 0);
    auto testFootage = Footage();
    dynamicArray1.addElementToPosition(testFootage, 0);
    assert(dynamicArray1.getSize() == 1);
    dynamicArray1.removeElementFromPosition(0);
    assert(dynamicArray1.getSize() == 0);
}

void TestDynamicArray::test_removeElementFromPosition_NegativePosition_Exception() {
    auto dynamicArray1 = DynamicArray<Footage>();
    assert(dynamicArray1.getSize() == 0);
    auto testFootage = Footage();
    dynamicArray1.addElementToPosition(testFootage, 0);
    assert(dynamicArray1.getSize() == 1);
    try {
        dynamicArray1.removeElementFromPosition(-1);
        assert(false);
    }catch (std::exception &) {
        static_assert(true);
    }
    assert(dynamicArray1.getSize() == 1);
}

void TestDynamicArray::test_setElement_ValidPosition_ElementSet() {
    auto dynamicArray1 = DynamicArray<Footage>();
    assert(dynamicArray1.getSize() == 0);
    auto testFootage = Footage();
    dynamicArray1.addElementToPosition(testFootage, 0);
    dynamicArray1.setElement(Footage("abc", "def", Date(), 7, "ghi"), 0);
    assert(dynamicArray1.getElement(0).getTitle() == "abc");
}

void TestDynamicArray::test_setElement_NegativePosition_Exception() {
    auto dynamicArray1 = DynamicArray<Footage>();
    assert(dynamicArray1.getSize() == 0);
    auto testFootage = Footage();
    dynamicArray1.addElementToPosition(testFootage, 0);
    try {
        dynamicArray1.setElement(Footage("abc", "def", Date(), 7, "ghi"), -1);
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

