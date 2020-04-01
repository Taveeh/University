//
// Created by Octavian Custura on 24/03/2020.
//

#ifndef ASSIGNMENT_5_6_TESTREPOSITORY_H
#define ASSIGNMENT_5_6_TESTREPOSITORY_H


class TestRepository {
public:
    static void test_all();

private:
    static void test_addFootage_ValidInput_FootageAdded();

    static void test_addFootage_Duplicate_FootageNotAdded();

    static void test_deleteFootage_ValidInput_FootageRemoved();

    static void test_deleteFootage_Inexistent_FootageNotRemoved();

    static void test_updateFootage_ValidInput_FootageChanged();

    static void test_updateFootage_Inexistent_FootageNotChanged();

};


#endif //ASSIGNMENT_5_6_TESTREPOSITORY_H
