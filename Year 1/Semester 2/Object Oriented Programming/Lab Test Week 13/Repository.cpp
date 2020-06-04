#include "Repository.h"

Repository::Repository(std::vector<Car> Container) 
 : Container(Container)
{

}

std::vector<Car> Repository::getContainer() 
{
	return this->Container;
}

void Repository::setContainer(std::vector<Car> Container) 
{
	this->Container = Container;
}

void Repository::add(Car newObject) 
{
//	if(this->isInRepo(newObject.getmanufacturer()))
//		throw(std::runtime_error("Object already in repository!"));
	this->Container.push_back(newObject);
}

void Repository::update(Car oldObject, Car newObject) 
{
	std::replace_if(Container.begin(), Container.end(),
		[&](Car currentObject){
		return currentObject == oldObject; },
 newObject);
}

void Repository::remove(Car targetObject) 
{
//	if(!this->isInRepo(targetObject.getmanufacturer()))
//		throw(std::runtime_error("Object is not in repository!"));
	Container = std::vector<Car>(Container.begin(), std::remove_if(Container.begin(), Container.end(),
		[&](Car currentObject){
		return currentObject == targetObject; }));
}

Car Repository::find(std::string manufacturer) 
{
	auto iterator = (std::find_if(Container.begin(), Container.end(),
	[&](Car currentObject){
	return currentObject.getmanufacturer() == manufacturer;
	}));
//	if(iterator == Container.end())
//		 throw(std::runtime_error("Object not found in repository"));
//	else
return *iterator;

}

bool Repository::isInRepo(std::string manufacturer) 
{
	return (std::find_if(Container.begin(), Container.end(),
	[&](Car currentObject){
	return currentObject.getmanufacturer() == manufacturer;
	})) != 
	Container.end();

}

//{memberFunction}