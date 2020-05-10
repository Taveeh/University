//
// Created by Octavian Custura on 04/05/2020.
//

#ifndef LAB_TEST_WEEK_10_UI_H
#define LAB_TEST_WEEK_10_UI_H
#include "Service.h"

class UI {
private:
	Service service;
	void add(const std::string& parameters);
	void list(const std::string& parameters);
	void addFile(const std::string parameters);
	void setFile(const std::string parameters);

public:
	UI();
	void runProgram();
};


#endif //LAB_TEST_WEEK_10_UI_H
