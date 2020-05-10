//
// Created by Octavian Custura on 24/03/2020.
//

#ifndef ASSIGNMENT_5_6_TESTSERVICE_H
#define ASSIGNMENT_5_6_TESTSERVICE_H


class TestService {
public:
	static void test_all();

private:
	// -----------------------Validate Date ---------------------//
	static void test_addFootage_InvalidDateNovember31st_FootageNotAdded();
	static void test_addFootage_InvalidDateFebruary31st_FootageNotAdded();
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

	// ------------------------ GET CURRENT ---------------------------//
	static void test_getCurrent_ValidInput_GetCurrentElement();

	// -------------------- ADD TO MY LIST ----------------------------//
	static void test_addToMyList_ValidInput_ElementAdded();
	static void test_addToMyList_InvalidInput_ThrowsException();

	static void test_getFilteredList_NegativeAccessed_ThrowsException();
	static void test_getFilteredList_ValidInput_GetsList();




};


#endif //ASSIGNMENT_5_6_TESTSERVICE_H
