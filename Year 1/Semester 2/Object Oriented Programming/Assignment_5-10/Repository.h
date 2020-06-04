//
// Created by Octavian Custura on 12/04/2020.
//

#ifndef ASSIGNMENT_7_8_REPOSITORY_H
#define ASSIGNMENT_7_8_REPOSITORY_H

#include "Footage.h"
#include "Exceptions.h"
#include <vector>

class Repository {
	/*
	 * Repository Interface
	 */
public:
	virtual ~Repository() = default;

	virtual void addFootage(const Footage& newFootage) = 0;

	virtual void deleteFootage(const std::string& titleToBeRemoved) = 0;

	virtual void updateFootage(const Footage& newFootage) = 0;

	virtual std::vector<Footage> getAllFootage() = 0;

	virtual Footage getCurrentElement() = 0;

	virtual void openList() = 0;
};



#endif //ASSIGNMENT_7_8_REPOSITORY_H
