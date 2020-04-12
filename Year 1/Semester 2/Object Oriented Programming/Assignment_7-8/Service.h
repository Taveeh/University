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
	FileRepository repository;

	MemoryRepository myListRepository;
	static bool validateNewDate(int day, int month, int year);
public:
	Service();

	explicit Service(FileRepository& newRepository);

	void addFootage(const std::string &title, const std::string &type, const std::string &dateString, const std::string &numberAccessedString, const std::string &link);

	void deleteFootage(const std::string& title);

	void updateFootage(const std::string &title, const std::string &type, const std::string &dateString, const std::string &numberAccessedString, const std::string &link);

	std::vector<Footage> getAllElements();

	[[nodiscard]] Footage getCurrent();

	void addToMyList(const std::string& title);

	std::vector<Footage> getMyList();

	std::vector<Footage> getFilteredList(const std::string& type, const std::string& maximumAccessCount);

	void setPath(const std::string& fileName);
};

#endif //ASSIGNMENT_5_6_SERVICE_H
