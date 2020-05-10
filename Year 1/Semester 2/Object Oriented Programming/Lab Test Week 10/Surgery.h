//
// Created by Octavian Custura on 04/05/2020.
//

#ifndef LAB_TEST_WEEK_10_SURGERY_H
#define LAB_TEST_WEEK_10_SURGERY_H
#include "HospitalDepartment.h"

class Surgery: public HospitalDepartment {
private:
	int numberOfPatients;
public:
	Surgery(const std::string& newHospitalName, int numberOfDoctors, int numberOfPatients);
	bool isEfficient() override;
	std::string toString() override;
};


#endif //LAB_TEST_WEEK_10_SURGERY_H
