//
// Created by Octavian Custura on 24/03/2020.
//

#include "TestFileRepository.h"
#include "Footage.h"
#include "FileRepository.h"
#include <exception>
#include <cassert>

void TestFileRepository::test_addFootage_ValidInput_FootageAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	assert(repository.getAllFootage().size() == 1);
}

void TestFileRepository::test_all() {
	test_addFootage_ValidInput_FootageAdded();
	test_addFootage_Duplicate_FootageNotAdded();
	test_deleteFootage_ValidInput_FootageRemoved();
	test_deleteFootage_Inexistent_FootageNotRemoved();
	test_updateFootage_Inexistent_FootageNotChanged();
	test_updateFootage_ValidInput_FootageChanged();
	test_getCurrentElement_EndOfArray_FirstElement();
}

void TestFileRepository::test_addFootage_Duplicate_FootageNotAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	auto testFootage2 = Footage("abc", "efg", Date(3, 3, 2020), 9, "link2");
	try {
		repository.addFootage(testFootage2);
	}catch (std::exception&) {
		assert(true);
	}
}

void TestFileRepository::test_deleteFootage_ValidInput_FootageRemoved() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	repository.deleteFootage("abc");
	assert(repository.getAllFootage().size() == 0);
}

void TestFileRepository::test_deleteFootage_Inexistent_FootageNotRemoved() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	try {
		repository.deleteFootage("abd");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestFileRepository::test_updateFootage_ValidInput_FootageChanged() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	auto testFootage2 = Footage("abc", "efg", Date(3, 3, 2020), 9, "link2");
	repository.updateFootage(testFootage2);
	assert(repository.getAllFootage()[0].getType() == "efg");
}

void TestFileRepository::test_updateFootage_Inexistent_FootageNotChanged() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	auto testFootage2 = Footage("abd", "efg", Date(3, 3, 2020), 9, "link2");
	try {
		repository.updateFootage(testFootage2);
	}catch (std::exception&) {
		assert(true);
	}
}

void TestFileRepository::test_getCurrentElement_EndOfArray_FirstElement() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
	repository.addFootage(testFootage);
	testFootage = repository.getCurrentElement();
	testFootage = repository.getCurrentElement();
	assert(testFootage.getTitle() == "abc");
}
