//
// Created by Octavian Custura on 20/06/2020.
//

#ifndef FINALEXAM_SERVICE_H
#define FINALEXAM_SERVICE_H
#include <utility>
#include "Domain.h"
#include "Repository.h"

class Service {
private:
	std::string fileName;
	std::vector<Astronomer> astronomers;
	Repository<Star> repository;
	void read();
public:
	Service(std::string fileName1, std::string fileName2);
	std::vector<Star> getAllStars() const;
	std::vector<Astronomer> getAllAstronomers() const;
	std::vector<Star> getStarsByName(std::string name) const;
	void addStar(std::string name, std::string constelation, int x, int y, int d);
	std::vector<Star> getStarByConstellation(std::string constellation) const;
};


#endif //FINALEXAM_SERVICE_H
