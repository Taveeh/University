//
// Created by Octavian Custura on 23/03/2020.
//

#ifndef ASSIGNMENT_5_6_TESTDYNAMICARRAY_H
#define ASSIGNMENT_5_6_TESTDYNAMICARRAY_H


class TestDynamicArray {
public:
    static void test_all();

private:
    static void test_CopyConstructor_ValidArray_AllAreTheSame();

    static void test_AssignmentOperator_ValidArray_AllAreTheSame();

    static void test_addElement_ValidElement_ElementAdded();

    static void test_addElementToPosition_ValidPosition_ElementAdded();

    static void test_addElementToPosition_NegativePosition_Exception();

    static void test_removeElementFromPosition_ValidPosition_ElementRemoved();

    static void test_removeElementFromPosition_NegativePosition_Exception();

    static void test_setElement_ValidPosition_ElementSet();

    static void test_setElement_NegativePosition_Exception();
};


#endif //ASSIGNMENT_5_6_TESTDYNAMICARRAY_H
