//
// Created by Octavian Custura on 04/05/2020.
//

#ifndef LAB_TEST_WEEK_10_CONTROLLER_H
#define LAB_TEST_WEEK_10_CONTROLLER_H
#include <vector>
#include "HospitalDepartment.h"
class Controller {
private:
	std::vector<HospitalDepartment*> arrayOfHospitalDepartments;
public:
	Controller();
	void addDepartment(HospitalDepartment* newHospitalDepartment);
	std::vector<HospitalDepartment*> getAllDepartments();
	std::vector<HospitalDepartment*> getAllEfficientDepartments();
	void writeToFile(const std::string& filename);
};


#endif //LAB_TEST_WEEK_10_CONTROLLER_H
