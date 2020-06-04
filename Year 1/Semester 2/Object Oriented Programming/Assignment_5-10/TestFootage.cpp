//
// Created by Octavian Custura on 21/03/2020.
//
#include "TestFootage.h"
#include "Footage.h"
#include <iostream>

void TestFootage::test_all() {
	test_compareDate_differentDays_IncreasingDates();
	test_compareDate_differentMonths_DecreasingDates();
	test_compareDate_differentMonths_IncreasingDates();
	test_compareDate_differentYears_DecreasingDates();
	test_compareDate_differentYears_IncreasingDates();
	test_dateToString_emptyDate_zeroDate();
	test_changeType_ValidInput_FootageChanged();
	test_changeAccessCount_ValidInput_FootageChanged();
	test_changeDate_ValidInput_FootageChanged();
	test_changeLink_ValidInput_FootageChanged();
	test_footageToString_emptyFootage_emptyString();
}

void TestFootage::test_compareDate_differentDays_IncreasingDates() {
	auto Date1 = Date(12, 12, 2020);
	auto Date2 = Date(13, 12, 2020);
	assert(Date1 < Date2);
}

void TestFootage::test_dateToString_emptyDate_zeroDate() {
	auto date = Date();
	assert(date.toString() == "00-00-0");
}

void TestFootage::test_changeType_ValidInput_FootageChanged() {
	Footage footage = Footage("abc", "def", Date(2, 2, 2020), 8, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
	footage.changeType("efg");
	assert(footage.getType() == "efg");
}

void TestFootage::test_changeLink_ValidInput_FootageChanged() {
	Footage footage = Footage("abc", "def", Date(2, 2, 2020), 8, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
	footage.changeLink("Never gonna give you up");
	assert(footage.getLink() == "Never gonna give you up");
}

void TestFootage::test_changeDate_ValidInput_FootageChanged() {
	Footage footage = Footage("abc", "def", Date(2, 2, 2020), 8, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
	footage.changeDate(Date(3, 3, 2019));
	assert(footage.getDate().getDay() == 3);
}

void TestFootage::test_changeAccessCount_ValidInput_FootageChanged() {
	Footage footage = Footage("abc", "def", Date(2, 2, 2020), 8, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
	footage.changeAccessCount(9);
	assert(footage.getAccessCount() == 9);
}

void TestFootage::test_compareDate_differentYears_IncreasingDates() {
	auto Date1 = Date(12, 12, 2019);
	auto Date2 = Date(13, 12, 2020);
	assert(Date1 < Date2);
}

void TestFootage::test_compareDate_differentMonths_IncreasingDates() {
	auto Date1 = Date(12, 11, 2020);
	auto Date2 = Date(13, 12, 2020);
	assert(Date1 < Date2);
}

void TestFootage::test_compareDate_differentMonths_DecreasingDates() {
	auto Date1 = Date(12, 12, 2020);
	auto Date2 = Date(13, 11, 2020);
	assert(!(Date1 < Date2));
}

void TestFootage::test_compareDate_differentYears_DecreasingDates() {
	auto Date1 = Date(12, 12, 2020);
	auto Date2 = Date(13, 12, 2019);
	assert(!(Date1 < Date2));
}

void TestFootage::test_footageToString_emptyFootage_emptyString() {
	auto footage = Footage();
	assert(footage.toString() == "Title:  Type:  Date: 00-00-0 Access count: 0 Link: ");
}
