//
// Created by Octavian Custura on 19/03/2020.
//

#ifndef ASSIGNMENT_5_6_SERVICE_H
#define ASSIGNMENT_5_6_SERVICE_H

#include <string>
#include "FileRepository.h"
#include "MemoryRepository.h"

#define SIZE_OF_DATE 10
class Service {
private:
	Repository* repository;

	Repository* myListRepository;

	/*
	 * Validates if the added date is valid
	 * Input:
	 *  day, month, year - int
	 * Output:
	 *
	 */
	static bool validateNewDate(int day, int month, int year);
public:
//	/*
//	 * Default constructor
//	 */
//	Service();

	/*
	 * Constructor
	 */
	explicit Service();

	/*
	 * Function that adds a footage
	 * Input:
	 *  title, type, dateString, numberAccessedString, link - std::string
	 * Throws:
	 *  std::exception() if footage not valid
	 *  std::exception() if footage already exists
	 */
	void addFootage(const std::string &title, const std::string &type, const std::string &dateString, const std::string &numberAccessedString, const std::string &link);

	/*
	 * Function that deletes a footage
	 * Input:
	 *  title - std::string
	 * Throws:
	 *  std::exception() if footage does not exist
	 */
	void deleteFootage(const std::string& title);

	/*
	 * Function that updates a footage
	 * Input:
	 *  title, type, dateString, numberAccessedString, link - std::string
	 * Throws:
	 *  std::exception() if footage does not exist
	 *  std::exception() if footage not valid
	 */
	void updateFootage(const std::string &title, const std::string &type, const std::string &dateString, const std::string &numberAccessedString, const std::string &link);

	/*
	 * Returns all the footage
	 * Input:
	 * Output:
	 * std::vector<Footage> - list of footage
	 */
	std::vector<Footage> getAllElements();

	/*
	 * Returns the current element
	 * Input:
	 * Output:
	 * Footage - current element
	 */
	[[nodiscard]] Footage getCurrent();

	/*
	 * Adds footage to my list
	 * Input:
	 *  title - std::string
	 * Throws:
	 *  std::exception() if footage does not exist
	 */
	void addToMyList(const std::string& title);

	/*
	 * Returns my list
	 * Input:
	 * Output:
	 *  std::vector<Footage> - my list
	 */
	std::vector<Footage> getMyList();

	/*
	 * Gets the list filtered by type with access count smaller than given number
	 * Input:
	 *  type, maximumAccessCount - std::string
	 * Output:
	 *  std::vector<Footage> - filtered list of footage
	 */
	std::vector<Footage> getFilteredList(const std::string& type, const std::string& maximumAccessCount);

	/*
	 * Function that sets path for the file repository
	 */
	void setPath(const std::string& fileName);

	~Service();
};

#endif //ASSIGNMENT_5_6_SERVICE_H
