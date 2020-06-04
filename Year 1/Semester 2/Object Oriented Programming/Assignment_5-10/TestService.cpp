//
// Created by Octavian Custura on 24/03/2020.
//

#include "TestService.h"
#include "Service.h"
#include <fstream>
void TestService::test_all() {
	std::ofstream clearFile;
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addFootage_ValidInput_FootageAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addFootage_InvalidDateFormat_FootageNotAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addFootage_InvalidDate_FootageNotAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addFootage_FutureDate_FootageNotAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addFootage_InvalidAccessCount_FootageNotAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addFootage_DuplicateFootage_FootageNotAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_deleteFootage_ValidInput_FootageRemoved();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_deleteFootage_Inexistent_FootageNotRemoved();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_updateFootage_ValidInput_FootageChanged();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_updateFootage_InvalidDateFormat_FootageNotChanged();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_updateFootage_InvalidDate_FootageNotChanged();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_updateFootage_FutureDate_FootageNotChanged();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_updateFootage_InvalidAccessCount_FootageNotChanged();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_getCurrent_ValidInput_GetCurrentElement();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addToMyList_InvalidInput_ThrowsException();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	clearFile.open("test.csv", std::ofstream::out | std::ostream::trunc);
	clearFile.close();
	test_addToMyList_ValidInput_ElementAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_getFilteredList_NegativeAccessed_ThrowsException();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_getFilteredList_ValidInput_GetsList();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addFootage_InvalidDateFebruary31st_FootageNotAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
	test_addFootage_InvalidDateNovember31st_FootageNotAdded();
	clearFile.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	clearFile.close();
}

void TestService::test_addFootage_ValidInput_FootageAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	assert(service.getAllElements().size() == 1);
}

void TestService::test_addFootage_InvalidDateFormat_FootageNotAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	try {
		service.addFootage("abc", " def", " 02-02-2020dfsads", " 7", " link");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_addFootage_InvalidDate_FootageNotAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	try {
		service.addFootage("abc", " def", " 2020-02-02", " 7", " link");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_addFootage_FutureDate_FootageNotAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	try {
		service.addFootage("abc", " def", " 02-02-2021", " 7", " link");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_addFootage_InvalidAccessCount_FootageNotAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	try {
		service.addFootage("abc", " def", " 02-02-2020", " -2", " link");
	}catch (ValidationException&) {
		static_assert(true, "");
	}

}

void TestService::test_addFootage_DuplicateFootage_FootageNotAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_deleteFootage_ValidInput_FootageRemoved() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	service.deleteFootage("abc");
	assert(service.getAllElements().empty());
}

void TestService::test_deleteFootage_Inexistent_FootageNotRemoved() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	try {
		service.deleteFootage("abc");
	}catch (RepositoryException&) {
		static_assert(true, "");
	}
}

void TestService::test_updateFootage_ValidInput_FootageChanged() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage(" abc", " def", " 02-02-2020", " 7", " link");
	service.updateFootage(" abc", " efg", " 03-03-2019", " 9", " link2");
	assert(service.getAllElements()[0].getType() == "efg");
}

void TestService::test_updateFootage_InvalidDateFormat_FootageNotChanged() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.updateFootage("abc", " efg", " 02-02-2020dfsfa", " 9", " link2");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_updateFootage_InvalidDate_FootageNotChanged() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.updateFootage("abc", " efg", " 2020-02-02", " 9", " link2");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_updateFootage_FutureDate_FootageNotChanged() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.updateFootage("abc", " efg", " 03-03-2021", " 9", " link2");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_updateFootage_InvalidAccessCount_FootageNotChanged() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.updateFootage("abc", " efg", " 2020-02-02", " -9", " link2");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_getCurrent_ValidInput_GetCurrentElement() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	assert(service.getCurrent().getTitle() == "abc");
}

void TestService::test_addToMyList_ValidInput_ElementAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	std::string fileMyList = "test.csv";
	service.setPath(fileMyList, "mylist");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	service.addToMyList("abc");
	assert(service.getMyList().size() == 1);
}

void TestService::test_addToMyList_InvalidInput_ThrowsException() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	std::string fileMyList = "test.csv";
	service.setPath(fileMyList, "mylist");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.addToMyList("bcd");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_getFilteredList_NegativeAccessed_ThrowsException() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	service.addFootage("bcd", " def", " 02-02-2020", " 10", " link");
	service.addFootage("cde", " ghi", " 02-02-2020", " 7", " link");
	service.addFootage("efg", " ghi", " 02-02-2020", " 10", " link");
	try {
		auto filteredList = service.getFilteredList("def", " -1");
	}catch (ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_getFilteredList_ValidInput_GetsList() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	service.addFootage("bcd", " def", " 02-02-2020", " 10", " link");
	service.addFootage("cde", " ghi", " 02-02-2020", " 7", " link");
	service.addFootage("efg", " ghi", " 02-02-2020", " 10", " link");
	assert(service.getFilteredList("def", " 9").size() == 1);
}

void TestService::test_addFootage_InvalidDateNovember31st_FootageNotAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	try {
		service.addFootage("abc", " def", " 11-31-2019", " 7", " link");
	}catch(ValidationException&) {
		static_assert(true, "");
	}
}

void TestService::test_addFootage_InvalidDateFebruary31st_FootageNotAdded() {
	std::string file = "test.txt";
	auto service = Service();
	service.setPath(file, "repository");
	try {
		service.addFootage("abc", " def", " 02-31-2019", " 7", " link");
	}catch(ValidationException&) {
		static_assert(true, "");
	}
}




