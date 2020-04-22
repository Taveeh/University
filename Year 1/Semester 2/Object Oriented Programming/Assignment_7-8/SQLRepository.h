//
// Created by Octavian Custura on 21/04/2020.
//

#ifndef ASSIGNMENT_7_8_SQLREPOSITORY_H
#define ASSIGNMENT_7_8_SQLREPOSITORY_H

#include <string>
#include <sqlite3.h>
#include "Repository.h"
class SQLRepository: public Repository {
private:
	sqlite3 *database{};
	int currentElement;
public:
	explicit SQLRepository(const std::string& databaseName);

	void addFootage(const Footage& newFootage) override;

	void deleteFootage(const std::string& title) override;

	void updateFootage(const Footage& newFootage) override;

	Footage getCurrentElement() override;

	std::vector<Footage> getAllFootage() override;

	void openList() override {}

	~SQLRepository() override;

};


#endif //ASSIGNMENT_7_8_SQLREPOSITORY_H
