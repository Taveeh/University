//
// Created by Octavian Custura on 24/03/2020.
//

#include "TestService.h"
#include "Service.h"
#include <exception>
#include <cassert>

void TestService::test_all() {
	test_addFootage_ValidInput_FootageAdded();
	test_addFootage_InvalidDateFormat_FootageNotAdded();
	test_addFootage_InvalidDate_FootageNotAdded();
	test_addFootage_FutureDate_FootageNotAdded();
	test_addFootage_InvalidAccessCount_FootageNotAdded();
	test_addFootage_DuplicateFootage_FootageNotAdded();

	test_deleteFootage_ValidInput_FootageRemoved();
	test_deleteFootage_Inexistent_FootageNotRemoved();

	test_updateFootage_ValidInput_FootageChanged();
	test_updateFootage_InvalidDateFormat_FootageNotChanged();
	test_updateFootage_InvalidDate_FootageNotChanged();
	test_updateFootage_FutureDate_FootageNotChanged();
	test_updateFootage_InvalidAccessCount_FootageNotChanged();

	test_getCurrent_ValidInput_GetCurrentElement();

	test_addToMyList_InvalidInput_ThrowsException();
	test_addToMyList_ValidInput_ElementAdded();

	test_getFilteredList_NegativeAccessed_ThrowsException();
	test_getFilteredList_ValidInput_GetsList();

	test_setPath_InvalidInput_ThrowsException();
	test_setPath_ValidInput_PathChanged();

	test_addFootage_InvalidDateFebruary31st_FootageNotAdded();
	test_addFootage_InvalidDateNovember31st_FootageNotAdded();

}

void TestService::test_addFootage_ValidInput_FootageAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	assert(service.getAllElements().size() == 1);
}

void TestService::test_addFootage_InvalidDateFormat_FootageNotAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	try {
		service.addFootage("abc", " def", " 02-02-2020dfsads", " 7", " link");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_addFootage_InvalidDate_FootageNotAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	try {
		service.addFootage("abc", " def", " 2020-02-02", " 7", " link");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_addFootage_FutureDate_FootageNotAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	try {
		service.addFootage("abc", " def", " 02-02-2021", " 7", " link");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_addFootage_InvalidAccessCount_FootageNotAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	try {
		service.addFootage("abc", " def", " 02-02-2020", " -2", " link");
	}catch (std::exception&) {
		assert(true);
	}

}

void TestService::test_addFootage_DuplicateFootage_FootageNotAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_deleteFootage_ValidInput_FootageRemoved() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	service.deleteFootage("abc");
	assert(service.getAllElements().empty());
}

void TestService::test_deleteFootage_Inexistent_FootageNotRemoved() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	try {
		service.deleteFootage("abc");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_updateFootage_ValidInput_FootageChanged() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage(" abc", " def", " 02-02-2020", " 7", " link");
	service.updateFootage(" abc", " efg", " 03-03-2019", " 9", " link2");
	assert(service.getAllElements()[0].getType() == "efg");
}

void TestService::test_updateFootage_InvalidDateFormat_FootageNotChanged() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.updateFootage("abc", " efg", " 02-02-2020dfsfa", " 9", " link2");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_updateFootage_InvalidDate_FootageNotChanged() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.updateFootage("abc", " efg", " 2020-02-02", " 9", " link2");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_updateFootage_FutureDate_FootageNotChanged() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.updateFootage("abc", " efg", " 03-03-2021", " 9", " link2");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_updateFootage_InvalidAccessCount_FootageNotChanged() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.updateFootage("abc", " efg", " 2020-02-02", " -9", " link2");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_getCurrent_ValidInput_GetCurrentElement() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	assert(service.getCurrent().getTitle() == "abc");
}

void TestService::test_addToMyList_ValidInput_ElementAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	service.addToMyList("abc");
	assert(service.getMyList().size() == 1);
}

void TestService::test_addToMyList_InvalidInput_ThrowsException() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	try {
		service.addToMyList("bcd");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_setPath_ValidInput_PathChanged() {
	std::string file = " ";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	file = "test.txt";
	service.setPath(file);
}

void TestService::test_setPath_InvalidInput_ThrowsException() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	file = " ";
	try {
		service.setPath(file);
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_getFilteredList_NegativeAccessed_ThrowsException() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	service.addFootage("bcd", " def", " 02-02-2020", " 10", " link");
	service.addFootage("cde", " ghi", " 02-02-2020", " 7", " link");
	service.addFootage("efg", " ghi", " 02-02-2020", " 10", " link");
	try {
		auto filteredList = service.getFilteredList("def", " -1");
	}catch (std::exception&) {
		assert(true);
	}
}

void TestService::test_getFilteredList_ValidInput_GetsList() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
	service.addFootage("bcd", " def", " 02-02-2020", " 10", " link");
	service.addFootage("cde", " ghi", " 02-02-2020", " 7", " link");
	service.addFootage("efg", " ghi", " 02-02-2020", " 10", " link");
	assert(service.getFilteredList("def", " 9").size() == 1);
}

void TestService::test_addFootage_InvalidDateNovember31st_FootageNotAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	try {
		service.addFootage("abc", " def", " 11-31-2019", " 7", " link");
	}catch(std::exception&) {
		assert(true);
	}
}

void TestService::test_addFootage_InvalidDateFebruary31st_FootageNotAdded() {
	std::string file = "test.txt";
	auto repository = FileRepository(file);
	auto service = Service(repository);
	try {
		service.addFootage("abc", " def", " 02-31-2019", " 7", " link");
	}catch(std::exception&) {
		assert(true);
	}
}




