//
// Created by Octavian Custura on 24/03/2020.
//

#ifndef ASSIGNMENT_5_6_TESTSERVICE_H
#define ASSIGNMENT_5_6_TESTSERVICE_H


class TestService {
public:
    static void test_all();

private:
    // ------------------------- ADD ----------------------------//
    static void test_addFootage_ValidInput_FootageAdded();
    static void test_addFootage_InvalidDateFormat_FootageNotAdded();
    static void test_addFootage_InvalidDate_FootageNotAdded();
    static void test_addFootage_FutureDate_FootageNotAdded();
    static void test_addFootage_InvalidAccessCount_FootageNotAdded();
    static void test_addFootage_DuplicateFootage_FootageNotAdded();

    // ----------------------- REMOVE --------------------------//
    static void test_deleteFootage_ValidInput_FootageRemoved();
    static void test_deleteFootage_Inexistent_FootageNotRemoved();

    // ----------------------- UPDATE --------------------------//
    static void test_updateFootage_ValidInput_FootageChanged();
    static void test_updateFootage_InvalidDateFormat_FootageNotChanged();
    static void test_updateFootage_InvalidDate_FootageNotChanged();
    static void test_updateFootage_FutureDate_FootageNotChanged();
    static void test_updateFootage_InvalidAccessCount_FootageNotChanged();
};


#endif //ASSIGNMENT_5_6_TESTSERVICE_H
