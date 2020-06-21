//
// Created by Octavian Custura on 20/06/2020.
//

#include "Domain.h"

Astronomer::Astronomer(const std::string &name, const std::string &constellation) : name(name),
                                                                                    constellation(constellation) {}

Astronomer::Astronomer() {}

const std::string &Astronomer::getName() const {
	return name;
}

void Astronomer::setName(const std::string &name) {
	Astronomer::name = name;
}

const std::string &Astronomer::getConstellation() const {
	return constellation;
}

void Astronomer::setConstellation(const std::string &constellation) {
	Astronomer::constellation = constellation;
}

std::ostream &operator<<(std::ostream &os, const Astronomer &astronomer) {
	os <<  astronomer.name << "," << astronomer.constellation;
	return os;
}

std::istream &operator>>(std::istream &is, Astronomer &astronomer) {
	std::string line;
	std::getline(is, line);
	std::string array[2];
	int index = 0;
	for (auto c: line) {
		if (c == ',') {
			index++;
		}else {
			array[index] += c;
		}
	}
	astronomer.setName(array[0]);
	astronomer.setConstellation(array[1]);
	return is;
}

const std::string &Star::getName() const {
	return name;
}

void Star::setName(const std::string &name) {
	Star::name = name;
}

const std::string &Star::getConstellation() const {
	return constellation;
}

void Star::setConstellation(const std::string &constellation) {
	Star::constellation = constellation;
}

int Star::getRightAscension() const {
	return rightAscension;
}

void Star::setRightAscension(int rightAscension) {
	Star::rightAscension = rightAscension;
}

int Star::getDeclination() const {
	return declination;
}

void Star::setDeclination(int declination) {
	Star::declination = declination;
}

int Star::getDiameter() const {
	return diameter;
}

void Star::setDiameter(int diameter) {
	Star::diameter = diameter;
}

Star::Star(const std::string &name, const std::string &constellation, int rightAscension, int declination, int diameter)
		: name(name), constellation(constellation), rightAscension(rightAscension), declination(declination),
		  diameter(diameter) {}

Star::Star() {}

bool Star::operator==(const Star &rhs) const {
	return name == rhs.name;
}

std::ostream &operator<<(std::ostream &os, const Star &star) {
	os << star.name << "," << star.constellation << ","
	   << star.rightAscension << "," << star.declination << "," << star.diameter;
	return os;
}

std::istream &operator>>(std::istream &is, Star &star) {
	std::string line;
	std::getline(is, line);
	std::string array[5];
	int index = 0;
	for (auto c: line) {
		if (c == ',') {
			index++;
		}else {
			array[index] += c;
		}
	}
	star.setName(array[0]);
	star.setConstellation(array[1]);
	star.setRightAscension(std::stoi(array[2]));
	star.setDeclination(std::stoi(array[3]));
	star.setDiameter(std::stoi(array[4]));
	return is;
}

std::string Star::toString() {
	std::string message =  name + ',' + constellation + ',' + std::to_string(rightAscension) + ',' + std::to_string(declination) + ',' + std::to_string(diameter);
	return message;
}
