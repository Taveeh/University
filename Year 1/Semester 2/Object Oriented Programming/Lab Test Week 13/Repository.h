#pragma once
#include "vector"
#include "Car.h"
#include "string"
#include "algorithm"
#include "exception"



class Repository 
{

private: 
	std::vector<Car> Container;
//{memberField}   
//{memberFunction} 

public: 
	Repository(std::vector<Car> Container = std::vector<Car>());
   
//{memberField}   
	std::vector<Car> getContainer();
	void setContainer(std::vector<Car> Container);
	void add(Car newObject = Car());
	void update(Car oldObject = Car(), Car newObject = Car());
	void remove(Car targetObject = Car());
	Car find(std::string manufacturer = std::string());
	bool isInRepo(std::string manufacturer = std::string());
//{memberFunction} 

};
