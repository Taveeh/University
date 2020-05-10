//
// Created by Octavian Custura on 04/05/2020.
//

#ifndef LAB_TEST_WEEK_10_HOSPITALDEPARTMENT_H
#define LAB_TEST_WEEK_10_HOSPITALDEPARTMENT_H
#include <string>

class HospitalDepartment {
protected:
	std::string hospitalName;
	int numberOfDoctors;
public:
	virtual bool isEfficient() = 0;
	virtual std::string toString() = 0;
};


#endif //LAB_TEST_WEEK_10_HOSPITALDEPARTMENT_H
