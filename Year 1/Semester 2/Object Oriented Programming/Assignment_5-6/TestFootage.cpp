//
// Created by Octavian Custura on 21/03/2020.
//
#include "TestFootage.h"
#include "Footage.h"
#include <cassert>

void TestFootage::test_all() {
    test_compareDate_IncreasingDates();
    test_dateToString_emptyDate_zeroDate();
    test_FootageGetterSetter_ValidFootage();
}

void TestFootage::test_compareDate_IncreasingDates() {
    auto Date1 = Date(12, 12, 2020);
    auto Date2 = Date(13, 12, 2020);
    assert(Date1 < Date2);
}

void TestFootage::test_dateToString_emptyDate_zeroDate() {
    auto date = Date();
    assert(date.toString() == "0-0-0");
}

void TestFootage::test_FootageGetterSetter_ValidFootage() {
    Footage footage = Footage("abc", "def", Date(2, 2, 2020), 8, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    assert(footage.getTitle() == "abc");
    assert(footage.getType() == "def");
    footage.changeType("efg");
    assert(footage.getType() == "efg");
    assert(footage.getDate().getDay() == 2);
    assert(footage.getDate().getMonth() == 2);
    assert(footage.getDate().getYear() == 2020);
    footage.changeDate(Date(3, 3, 2019));
    assert(footage.getDate().getDay() == 3);
    assert(footage.getDate().getMonth() == 3);
    assert(footage.getDate().getYear() == 2019);
    assert(footage.getAccessCount() == 8);
    footage.changeAccessCount(9);
    assert(footage.getAccessCount() == 9);
    assert(footage.getLink() == "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    footage.changeLink("You got Rickrolled");
    assert(footage.getLink() == "You got Rickrolled");
    assert(footage.toString().size() != 0);
}
