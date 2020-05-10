//
// Created by Octavian Custura on 12/04/2020.
//

#ifndef ASSIGNMENT_7_8_FILEREPOSITORY_H
#define ASSIGNMENT_7_8_FILEREPOSITORY_H

#include "Repository.h"
class FileRepository: public Repository {
private:
	const std::string& fileName;
	int currentElement;
public:

//	void setPath(const std::string& newFileName);

	explicit FileRepository(const std::string& fileName);
	/*
	 * Adds footage to the repository
	 * Input:
	 * newFootage - const Footage&
	 * Throws:
	 * std::exception() if same title exists
	 */
	void addFootage(const Footage& newFootage) override;

	/*
	 * Removes a footage from the repository
	 * Input:
	 * titleToBeRemoved - const std::string&
	 * Throws:
	 * std::exception() if title does not exist
	 */
	void deleteFootage(const std::string& titleToBeRemoved) override;

	/*
	 * Updates a footage from the repository
	 * Input:
	 * newFootage - const Footage&
	 * Throws:
	 * std::exception() if title does not exist
	 */
	void updateFootage(const Footage& newFootage) override;

	/*
	 * Function that gets all the footage from the repository
	 * Input:
	 *
	 * Output:
	 * std::vector<Footage> - vector of elements
	 */
	std::vector<Footage> getAllFootage() override;

	/*
	 * Function that returns the current element from the repository
	 * Input:
	 *
	 * Ouput:
	 * Footage - current element from repository
	 */
	Footage getCurrentElement() override;

	void openList() override;

};


#endif //ASSIGNMENT_7_8_FILEREPOSITORY_H
