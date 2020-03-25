//
// Created by Octavian Custura on 24/03/2020.
//

#include "TestRepository.h"
#include "Repository.h"
#include <exception>
void TestRepository::test_addFootage_ValidInput_FootageAdded() {
    auto repository = Repository();
    auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
    repository.addFootage(testFootage);
    assert(repository.getAllFootage().getSize() == 1);
}

void TestRepository::test_all() {
    test_addFootage_ValidInput_FootageAdded();
    test_addFootage_Duplicate_FootageNotAdded();
    test_deleteFootage_ValidInput_FootageRemoved();
    test_deleteFootage_Inexistent_FootageNotRemoved();
    test_updateFootage_Inexistent_FootageNotChanged();
    test_updateFootage_ValidInput_FootageChanged();
}

void TestRepository::test_addFootage_Duplicate_FootageNotAdded() {
    auto repository = Repository();
    auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
    repository.addFootage(testFootage);
    assert(repository.getAllFootage().getSize() == 1);
    auto testFootage2 = Footage("abc", "efg", Date(3, 3, 2020), 9, "link2");
    try {
        repository.addFootage(testFootage2);
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
    assert(repository.getAllFootage().getSize() == 1);
}

void TestRepository::test_deleteFootage_ValidInput_FootageRemoved() {
    auto repository = Repository();
    auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
    repository.addFootage(testFootage);
    assert(repository.getAllFootage().getSize() == 1);
    repository.deleteFootage("abc");
    assert(repository.getAllFootage().getSize() == 0);
}

void TestRepository::test_deleteFootage_Inexistent_FootageNotRemoved() {
    auto repository = Repository();
    auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
    repository.addFootage(testFootage);
    assert(repository.getAllFootage().getSize() == 1);
    try {
        repository.deleteFootage("abd");
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
    assert(repository.getAllFootage().getSize() == 1);
}

void TestRepository::test_updateFootage_ValidInput_FootageChanged() {
    auto repository = Repository();
    auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
    repository.addFootage(testFootage);
    assert(repository.getAllFootage().getSize() == 1);
    auto testFootage2 = Footage("abc", "efg", Date(3, 3, 2020), 9, "link2");
    repository.updateFootage(testFootage2);
    assert(repository.getAllFootage().getElement(0).getType() == "efg");
}

void TestRepository::test_updateFootage_Inexistent_FootageNotChanged() {
    auto repository = Repository();
    auto testFootage = Footage("abc", "def", Date(2, 2, 2020), 7, "link");
    repository.addFootage(testFootage);
    assert(repository.getAllFootage().getSize() == 1);
    auto testFootage2 = Footage("abd", "efg", Date(3, 3, 2020), 9, "link2");
    try {
        repository.updateFootage(testFootage2);
        assert(false);
    }catch (std::exception&) {
        static_assert(true);
    }
    assert(repository.getAllFootage().getElement(0).getType() != "efg");
}
