#pragma once
#include "Repository.h"
#include "string"
#include "fstream"



class Service 
{

private: 
	Repository ApplicationRepository;
	void test_getNumberByMan_validType_returnRightValue();
	void test_getNumberByMan_invalidType_returnZero();
public: 
	Service(Repository ApplicationRepository = Repository());
   
	void add(std::string manufacturer = std::string(), std::string model = std::string(), std::string year = std::string(), std::string colour = std::string());
	void update(std::string manufacturer = std::string(), std::string model = std::string(), std::string year = std::string(), std::string colour = std::string());
	void remove(std::string manufacturer = std::string());
	std::vector<Car> list();
	void readFromFile(std::string FilePath = std::string());
	int getNumberByMan(std::string man);

};
