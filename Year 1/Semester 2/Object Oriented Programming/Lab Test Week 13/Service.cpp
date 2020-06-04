#include "Service.h"

Service::Service(Repository ApplicationRepository) 
 : ApplicationRepository(ApplicationRepository)
{
	test_getNumberByMan_invalidType_returnZero();
	test_getNumberByMan_validType_returnRightValue();
}

void Service::add(std::string manufacturer, std::string model, std::string year, std::string colour) 
{
Car newObject(manufacturer, model, std::stoi(year), colour);
this->ApplicationRepository.add(newObject);

}

void Service::update(std::string manufacturer, std::string model, std::string year, std::string colour) 
{
Car newObject(manufacturer, model, std::stoi(year), colour);
Car oldObject = this->ApplicationRepository.find(newObject.getmanufacturer());
this->ApplicationRepository.update(oldObject, newObject);

}

void Service::remove(std::string manufacturer) 
{
Car targetObject = this->ApplicationRepository.find(manufacturer);
this->ApplicationRepository.remove(targetObject);

}

std::vector<Car> Service::list() 
{
return ApplicationRepository.getContainer();

}

void Service::readFromFile(std::string FilePath) 
{
	std::ifstream File(FilePath);
	const char* delim = "|";
	std::string objectLine;
	std::getline(File, objectLine);
	while(!objectLine.empty() && File) {
		std::vector<std::string> Fields;
		int current, previous = 0;
		current = objectLine.find(delim);
		while(current != std::string::npos) {
			std::string Field = objectLine.substr(previous, current - previous);
			const auto Begin = Field.find_first_not_of(" ");
			const auto End = Field.find_last_not_of(" ");
			Field = Field.substr(Begin, End - Begin + 1);
			Fields.push_back(Field);
			previous = current + 1;
			current = objectLine.find(delim, previous);
		}
//		Fields.push_back(objectLine.substr(previous, current - previous));
		std::string Field = objectLine.substr(previous, current - previous);
		const auto Begin = Field.find_first_not_of(" ");
		const auto End = Field.find_last_not_of(" ");
		Field = Field.substr(Begin, End - Begin + 1);
		Fields.push_back(Field);
//		previous = current + 1;
//		current = objectLine.find(delim, previous);
		std::getline(File, objectLine);
		this->add(Fields[0], Fields[1], Fields[2], Fields[3]);
	}

}

int Service::getNumberByMan(std::string man) {
	/*
	 * Function that counts the number of cars owned by a manufacturer
	 * Input:
	 *  std::string manufacturer
	 * Output:
	 *  int - number of cars for that manufacturer
	 */
	auto elems = ApplicationRepository.getContainer();
	int cnt = 0;
	for (auto elem: elems) {
		if (elem.getmanufacturer() == man) {
			cnt++;
		}
	}
	return cnt;
}

void Service::test_getNumberByMan_validType_returnRightValue() {
	this->add("Opel", "car", "2007", "blue");
	assert(getNumberByMan("Opel") == 1);
	this->remove("Opel");
}

void Service::test_getNumberByMan_invalidType_returnZero() {
	assert(getNumberByMan("-1") == 0);
}

//{memberFunction}