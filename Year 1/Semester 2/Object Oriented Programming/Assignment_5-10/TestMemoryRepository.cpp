//
// Created by Octavian Custura on 24/03/2020.
//

#include "TestMemoryRepository.h"

void TestMemoryRepository::test_addFootage_ValidInput_FootageAdded() {
	auto repository = MemoryRepository();
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	assert(repository.getAllFootage().size() == 1);
}

void TestMemoryRepository::test_all() {
	test_addFootage_ValidInput_FootageAdded();
	test_addFootage_Duplicate_FootageNotAdded();
	test_deleteFootage_ValidInput_FootageRemoved();
	test_deleteFootage_Inexistent_FootageNotRemoved();
	test_updateFootage_Inexistent_FootageNotChanged();
	test_updateFootage_ValidInput_FootageChanged();
	test_getCurrentElement_EndOfArray_FirstElement();
}

void TestMemoryRepository::test_addFootage_Duplicate_FootageNotAdded() {
	auto repository = MemoryRepository();
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	auto testFootage2 = Footage("abc", "efg", Date(3, 3, 2020), 9, "link2");
	try {
		repository.addFootage(testFootage2);
	}catch (RepositoryException&) {
		static_assert(true, "");
	}
}

void TestMemoryRepository::test_deleteFootage_ValidInput_FootageRemoved() {
	auto repository = MemoryRepository();
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	repository.deleteFootage("abc");
	assert(repository.getAllFootage().empty());
}

void TestMemoryRepository::test_deleteFootage_Inexistent_FootageNotRemoved() {
	auto repository = MemoryRepository();
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	try {
		repository.deleteFootage("abd");
	}catch (RepositoryException&) {
		static_assert(true, "");
	}
}

void TestMemoryRepository::test_updateFootage_ValidInput_FootageChanged() {
	auto repository = MemoryRepository();
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	auto testFootage2 = Footage("abc", "efg", Date(3, 3, 2020), 9, "link2");
	repository.updateFootage(testFootage2);
	assert(repository.getAllFootage()[0].getType() == "efg");
}

void TestMemoryRepository::test_updateFootage_Inexistent_FootageNotChanged() {
	auto repository = MemoryRepository();
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	auto testFootage2 = Footage("abd", "efg", Date(3, 3, 2020), 9, "link2");
	try {
		repository.updateFootage(testFootage2);
	}catch (RepositoryException&) {
		static_assert(true, "");
	}
}

void TestMemoryRepository::test_getCurrentElement_EndOfArray_FirstElement() {
	auto repository = MemoryRepository();
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	testFootage = Footage("abd", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	repository.getCurrentElement();
	repository.getCurrentElement();
	testFootage = repository.getCurrentElement();
	assert(testFootage.getTitle() == "abc");
}
