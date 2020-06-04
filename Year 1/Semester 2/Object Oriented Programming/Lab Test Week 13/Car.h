#pragma once
#include "string"



class Car 
{

private: 
	std::string manufacturer;
	std::string model;
	int year;
	std::string colour;
//{memberField}   
//{memberFunction} 

public: 
	Car(std::string manufacturer = std::string(), std::string model = std::string(), int year = 0, std::string colour = std::string());
   
//{memberField}   
	std::string getmanufacturer();
	void setmanufacturer(std::string manufacturer);
	std::string getmodel();
	void setmodel(std::string model);
	int getyear();
	void setyear(int year);
	std::string getcolour();
	void setcolour(std::string colour);
//{memberFunction} 

};
bool operator==(Car First, Car Second);
std::string to_string(Car targetObject);