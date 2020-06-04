//
// Created by Octavian Custura on 21/03/2020.
//

#ifndef ASSIGNMENT_5_6_TESTFOOTAGE_H
#define ASSIGNMENT_5_6_TESTFOOTAGE_H

class TestFootage {
private:
	static void test_compareDate_differentDays_IncreasingDates();

	static void test_compareDate_differentYears_IncreasingDates();

	static void test_compareDate_differentYears_DecreasingDates();

	static void test_compareDate_differentMonths_IncreasingDates();

	static void test_compareDate_differentMonths_DecreasingDates();

	static void test_dateToString_emptyDate_zeroDate();

	static void test_changeType_ValidInput_FootageChanged();

	static void test_changeDate_ValidInput_FootageChanged();

	static void test_changeAccessCount_ValidInput_FootageChanged();

	static void test_changeLink_ValidInput_FootageChanged();

	static void test_footageToString_emptyFootage_emptyString();
public:
	static void test_all();
};


#endif //ASSIGNMENT_5_6_TESTFOOTAGE_H
