//
// Created by Octavian Custura on 04/05/2020.
//

#ifndef LAB_TEST_WEEK_10_SERVICE_H
#define LAB_TEST_WEEK_10_SERVICE_H
#include "Controller.h"

class Service {
private:
	Controller controller;
public:
	Service();
	std::string file;
	void addDepartment(const std::string& parameters);
	std::vector<HospitalDepartment*> getAllDepartments();
	std::vector<HospitalDepartment*> getAllEfficient();
	void writeToFile();
	void setFile(const std::string& filename);
};


#endif //LAB_TEST_WEEK_10_SERVICE_H
