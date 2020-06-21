//
// Created by Octavian Custura on 20/06/2020.
//

#include "Service.h"

void Service::read() {
	std::ifstream fin(fileName);
	std::string elementString;
	std::getline(fin, elementString);
	Astronomer elem{};
	while(!elementString.empty()) {
		std::stringstream stringToElement(elementString);
		stringToElement >> elem;
		astronomers.push_back(elem);
		elementString.clear();
		std::getline(fin, elementString);
	}
	fin.close();
}

Service::Service(std::string fileName1, std::string fileName2) : fileName(std::move(fileName1)), repository(fileName2){
	read();
}

std::vector<Star> Service::getAllStars() const {
	auto a = repository.getAllElements();
	return a;
}

std::vector<Astronomer> Service::getAllAstronomers() const {
	return astronomers;
}

std::vector<Star> Service::getStarsByName(std::string name) const {
	auto a = repository.getAllElements();
	std::vector<Star> v;
	if (name.empty()) {
		return v;
	}
	for (auto el: a) {
		if (el.getName().find(name) != std::string::npos) {
			v.push_back(el);
		}
	}
	return v;
}

void Service::addStar(std::string name, std::string constelation, int x, int y, int d) {
	/*
	 * Function that adds a star in the repository
	 * Input:
	 *  name - std::string
	 *  constelation - std::string
	 *  x - int
	 *  y - int
	 *  d - int
	 * Throws:
	 *  Exception - if name is empty
	 *  Exception - if diameter is < 0
	 */
	if (name.empty()) {
		throw Exception("Empty name");
	}
	if (d < 0) {
		throw Exception("Diameter must be >=0");
	}
	repository.addElement(Star(name, constelation, x, y, d));
}

std::vector<Star> Service::getStarByConstellation(std::string constellation) const {
	auto a = repository.getAllElements();
	if (constellation.empty()) {
		return a;
	}
	std::vector<Star> v;
	for (auto el: a) {
		if (el.getConstellation() == constellation) {
			v.push_back(el);
		}
	}
	return v;
}
