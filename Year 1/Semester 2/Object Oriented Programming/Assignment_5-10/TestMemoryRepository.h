//
// Created by Octavian Custura on 12/04/2020.
//

#ifndef ASSIGNMENT_7_8_TESTMEMORYREPOSITORY_H
#define ASSIGNMENT_7_8_TESTMEMORYREPOSITORY_H

#include "MemoryRepository.h"

class TestMemoryRepository {
public:
	static void test_all();

private:
	static void test_addFootage_ValidInput_FootageAdded();

	static void test_addFootage_Duplicate_FootageNotAdded();

	static void test_deleteFootage_ValidInput_FootageRemoved();

	static void test_deleteFootage_Inexistent_FootageNotRemoved();

	static void test_updateFootage_ValidInput_FootageChanged();

	static void test_updateFootage_Inexistent_FootageNotChanged();

	static void test_getCurrentElement_EndOfArray_FirstElement();

};


#endif //ASSIGNMENT_7_8_TESTMEMORYREPOSITORY_H
