#include "Car.h"

Car::Car(std::string manufacturer, std::string model, int year, std::string colour) 
 : manufacturer(manufacturer), model(model), year(year), colour(colour)
{

}

std::string Car::getmanufacturer() 
{
	return this->manufacturer;
}

void Car::setmanufacturer(std::string manufacturer) 
{
	this->manufacturer = manufacturer;
}

std::string Car::getmodel() 
{
	return this->model;
}

void Car::setmodel(std::string model) 
{
	this->model = model;
}

int Car::getyear() 
{
	return this->year;
}

void Car::setyear(int year) 
{
	this->year = year;
}

std::string Car::getcolour() 
{
	return this->colour;
}

void Car::setcolour(std::string colour) 
{
	this->colour = colour;
}

//{memberFunction}
bool operator==(Car First, Car Second) 
{
	return 
First.getmanufacturer() == Second.getmanufacturer() &&
First.getmodel() == Second.getmodel() &&
First.getyear() == Second.getyear() &&
First.getcolour() == Second.getcolour() ;

}
std::string to_string(Car targetObject) 
{
	return
	" manufacturer: " + targetObject.getmanufacturer() +
	" model: " + targetObject.getmodel() +
	" year: " + std::to_string(targetObject.getyear()) +
	" colour: " + targetObject.getcolour() ;
}