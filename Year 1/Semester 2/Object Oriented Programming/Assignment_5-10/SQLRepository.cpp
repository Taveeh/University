//
// Created by Octavian Custura on 21/04/2020.
//

#include "SQLRepository.h"
#include <sstream>
#include <iostream>

SQLRepository::SQLRepository(const std::string& databaseName):currentElement(0) {
	int databaseFlag = sqlite3_open(databaseName.c_str(), &database);
	if (databaseFlag) {
		throw RepositoryException("Database could not be opened");
	}
	char* errorMessage = nullptr;
	std::string sqlStatement = "CREATE TABLE IF NOT EXISTS FOOTAGE(title text primary key not null, type text not null, date text not null, views int not null, link text not null );";
	if (sqlite3_exec(database, sqlStatement.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		throw RepositoryException("Cannot create table");
	}
}

void SQLRepository::addFootage(const Footage &newFootage) {
	std::string sqlStatement;
	sqlStatement = "INSERT INTO FOOTAGE (title, type, date, views, link) " \
					"VALUES (";
	sqlStatement += '\''  + newFootage.getTitle() + '\'' + ',' + ' ' + '\'' + newFootage.getType() + '\'' + ',' + ' ' + '\'' + newFootage.getDate().toString() + '\'' + ',' + ' ' + std::to_string(newFootage.getAccessCount()) + ',' + ' ' + '\'' + newFootage.getLink() + '\'' + ')' + ' ' + ';';
	char* errorMessage = nullptr;
	if (sqlite3_exec(database, sqlStatement.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		throw RepositoryException(errorMessage);
	}
}

SQLRepository::~SQLRepository() {
	sqlite3_close(database);
}

std::vector<Footage> SQLRepository::getAllFootage() {
	std::string sqlStatement = "SELECT title, type, date, views, link FROM FOOTAGE";
	sqlite3_stmt *stmt;
	std::vector<Footage> arrayOfFootage;
	if (sqlite3_prepare_v2(database, sqlStatement.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
		throw RepositoryException(sqlite3_errmsg(database));
	}
	int databaseFlag;
	while ((databaseFlag = sqlite3_step(stmt)) == SQLITE_ROW) {
		std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		std::string dateString = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		std::stringstream convertStringToDate(dateString);
		Date date;
		convertStringToDate >> date;
		int accessCount = sqlite3_column_int(stmt, 3);
		std::string link = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		arrayOfFootage.push_back(Footage(title, type, date, accessCount, link));
	}
	if (databaseFlag != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		throw sqlite3_errmsg(database);
	}
	sqlite3_finalize(stmt);
	return arrayOfFootage;
}

void SQLRepository::deleteFootage(const std::string &title) {
	std::string sqlStatement = "DELETE from FOOTAGE where title=\"" + title + "\";";
	if (sqlite3_exec(database, sqlStatement.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
		std::cout << sqlite3_errmsg(database) << std::endl;
		throw RepositoryException("Footage does not exist");
	}
}

void SQLRepository::updateFootage(const Footage &newFootage) {
	std::string sqlStatement = "UPDATE FOOTAGE set type = \"" + newFootage.getType() +  "\", date = \"" + newFootage.getDate().toString() + "\", views = " + std::to_string(newFootage.getAccessCount()) + ", link = \"" + newFootage.getLink() + "\" where title=\"" + newFootage.getTitle() + "\";";
	// ", date = " + newFootage.getDate().toString() + ", views = " + std::to_string(newFootage.getAccessCount()) + ", link = " + newFootage.getLink() +
	if (sqlite3_exec(database, sqlStatement.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
		std::cout << sqlite3_errmsg(database);
		throw RepositoryException("Footage does not exist");
	}
}

Footage SQLRepository::getCurrentElement() {
	std::vector<Footage> arrayOfFootage = getAllFootage();
	if (arrayOfFootage.size() == 0) {
		throw RepositoryException("There are no elements in the list");
	}
	if (currentElement == arrayOfFootage.size()) {
		currentElement = 0;
	}
	return (*(arrayOfFootage.begin() + currentElement++));
}

