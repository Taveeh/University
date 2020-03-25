//
// Created by Octavian Custura on 24/03/2020.
//

#include "TestService.h"
#include "Service.h"
#include <exception>

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

}

void TestService::test_addFootage_ValidInput_FootageAdded() {
    auto repository = Repository();
    auto service = Service(repository);
    service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
    assert(service.getAllElements().getSize() == 1);
    assert(service.getAllElements().getElement(0).getTitle() == "abc");
}

void TestService::test_addFootage_InvalidDateFormat_FootageNotAdded() {
    auto repository = Repository();
    auto service = Service(repository);
    try {
        service.addFootage("abc", " def", " 02-02-2020dfsads", " 7", " link");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

void TestService::test_addFootage_InvalidDate_FootageNotAdded() {
    auto repository = Repository();
    auto service = Service(repository);
    try {
        service.addFootage("abc", " def", " 2020-02-02", " 7", " link");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

void TestService::test_addFootage_FutureDate_FootageNotAdded() {
    auto repository = Repository();
    auto service = Service(repository);
    try {
        service.addFootage("abc", " def", " 02-02-2021", " 7", " link");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

void TestService::test_addFootage_InvalidAccessCount_FootageNotAdded() {
    auto repository = Repository();
    auto service = Service(repository);
    try {
        service.addFootage("abc", " def", " 02-02-2020", " -2", " link");
        assert(false);
    }catch (std::exception&) {
        static_assert(1);
    }

}

void TestService::test_addFootage_DuplicateFootage_FootageNotAdded() {
    auto repository = Repository();
    auto service = Service(repository);
    service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
    try {
        service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
        assert(false);
    }catch (std::exception&) {
        static_assert(1);
    }
}

void TestService::test_deleteFootage_ValidInput_FootageRemoved() {
    auto repository = Repository();
    auto service = Service(repository);
    service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
    assert(service.getAllElements().getSize() == 1);
    service.deleteFootage("abc");
    assert(service.getAllElements().getSize() == 0);
}

void TestService::test_deleteFootage_Inexistent_FootageNotRemoved() {
    auto repository = Repository();
    auto service = Service(repository);
    try {
        service.deleteFootage("abc");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

void TestService::test_updateFootage_ValidInput_FootageChanged() {
    auto repository = Repository();
    auto service = Service(repository);
    service.addFootage(" abc", " def", " 02-02-2020", " 7", " link");
    assert(service.getAllElements().getSize() == 1);
    service.updateFootage(" abc", " efg", " 03-03-2019", " 9", " link2");
    assert(service.getAllElements().getElement(0).getType() == "efg");
}

void TestService::test_updateFootage_InvalidDateFormat_FootageNotChanged() {
    auto repository = Repository();
    auto service = Service(repository);
    service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
    assert(service.getAllElements().getSize() == 1);
    try {
        service.updateFootage("abc", " efg", " 02-02-2020dfsfa", " 9", " link2");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

void TestService::test_updateFootage_InvalidDate_FootageNotChanged() {
    auto repository = Repository();
    auto service = Service(repository);
    service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
    assert(service.getAllElements().getSize() == 1);
    try {
        service.updateFootage("abc", " efg", " 2020-02-02", " 9", " link2");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

void TestService::test_updateFootage_FutureDate_FootageNotChanged() {
    auto repository = Repository();
    auto service = Service(repository);
    service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
    assert(service.getAllElements().getSize() == 1);
    try {
        service.updateFootage("abc", " efg", " 03-03-2021", " 9", " link2");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

void TestService::test_updateFootage_InvalidAccessCount_FootageNotChanged() {
    auto repository = Repository();
    auto service = Service(repository);
    service.addFootage("abc", " def", " 02-02-2020", " 7", " link");
    assert(service.getAllElements().getSize() == 1);
    try {
        service.updateFootage("abc", " efg", " 2020-02-02", " -9", " link2");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
}

