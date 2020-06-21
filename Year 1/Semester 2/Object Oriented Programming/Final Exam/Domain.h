//
// Created by Octavian Custura on 20/06/2020.
//

#ifndef FINALEXAM_DOMAIN_H
#define FINALEXAM_DOMAIN_H
#include <string>
#include <ostream>
#include <istream>
class Astronomer {
private:
	std::string name;
	std::string constellation;
public:
	Astronomer(const std::string &name, const std::string &constellation);

	Astronomer();

	const std::string &getName() const;

	void setName(const std::string &name);

	const std::string &getConstellation() const;

	void setConstellation(const std::string &constellation);

	friend std::ostream &operator<<(std::ostream &os, const Astronomer &astronomer);

	friend std::istream &operator>>(std::istream &is, Astronomer& astronomer);

};

class Star {
private:
	std::string name;
	std::string constellation;
	int rightAscension;
	int declination;
	int diameter;
public:
	const std::string &getName() const;

	void setName(const std::string &name);

	const std::string &getConstellation() const;

	void setConstellation(const std::string &constellation);

	int getRightAscension() const;

	void setRightAscension(int rightAscension);

	int getDeclination() const;

	void setDeclination(int declination);

	int getDiameter() const;

	void setDiameter(int diameter);

	Star();

	Star(const std::string &name, const std::string &constellation, int rightAscension, int declination, int diameter);

	bool operator==(const Star &rhs) const;

	friend std::ostream &operator<<(std::ostream &os, const Star &star);

	friend std::istream &operator>>(std::istream &is, Star& star);
	std::string toString();
};

#endif //FINALEXAM_DOMAIN_H
