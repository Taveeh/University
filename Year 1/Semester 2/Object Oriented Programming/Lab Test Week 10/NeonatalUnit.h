//
// Created by Octavian Custura on 04/05/2020.
//

#ifndef LAB_TEST_WEEK_10_NEONATALUNIT_H
#define LAB_TEST_WEEK_10_NEONATALUNIT_H
#include "HospitalDepartment.h"

class NeonatalUnit: public HospitalDepartment{
private:
		int numberOfMothers;
		int numberOfNewborns;
public:
		NeonatalUnit(const std::string& newHospitalName, int newNumberOfDoctors, int newNumberOfNewborns, int newNumberOfMothers, double newAverageGrade);
		double averageGrade;
		bool isEfficient() override;
		std::string toString() override;
};


#endif //LAB_TEST_WEEK_10_NEONATALUNIT_H
