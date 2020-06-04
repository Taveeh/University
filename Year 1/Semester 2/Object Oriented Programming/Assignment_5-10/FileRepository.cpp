//
// Created by Octavian Custura on 12/04/2020.
//

#include "FileRepository.h"
#include <fstream>
#include <iostream>

FileRepository::FileRepository(std::string file): fileName(std::move(file)), currentElement(0) {
	std::ifstream doesFileExist(fileName);
	if (!doesFileExist) {
		std::ofstream createFileToExist(fileName);
		createFileToExist.close();
	}
	doesFileExist.close();
}

void FileRepository::addFootage(const Footage &newFootage) {
	Footage footage;
	std::ifstream fileIn(fileName);
	std::vector<Footage> arrayOfFootage;
	while (fileIn >> footage) {
		if (footage.getTitle().empty()) break;
		if (footage.getTitle() == newFootage.getTitle()) {
			throw RepositoryException("Duplicate footage");
		}
		arrayOfFootage.push_back(footage);
	}
	fileIn.close();
	arrayOfFootage.push_back(newFootage);

	std::ofstream fileOut(fileName);
	for (const auto& footageElement: arrayOfFootage) {
		fileOut << footageElement;
	}
	fileOut.close();
}

void FileRepository::deleteFootage(const std::string &titleToBeRemoved) {
	std::vector<Footage> arrayOfFootage;
	Footage footage;
	std::ifstream fileIn(fileName);
	bool ok = true;
	std::string lineFootage;
	while (fileIn >> footage) {
		if (footage.getTitle() == titleToBeRemoved) {
			ok = false;
		}else arrayOfFootage.push_back(footage);
	}
	if (ok) {
		throw RepositoryException("Footage does not exist");
	}
	fileIn.close();
	std::ofstream fileOut(fileName);
	for (const auto& footageToFile: arrayOfFootage) fileOut << footageToFile;
	fileOut.close();
}

void FileRepository::updateFootage(const Footage &newFootage) {
	std::vector<Footage> arrayOfFootage;
	Footage footage;
	std::ifstream fileIn(fileName);
	bool ok = true;
	while (fileIn >> footage) {
		if (footage.getTitle() == newFootage.getTitle()) {
			arrayOfFootage.push_back(newFootage);
			ok = false;
		} else arrayOfFootage.push_back(footage);
	}
	if (ok) throw RepositoryException("Footage does not exist");
	fileIn.close();
	std::ofstream fileOut(fileName);
	for (const auto& footageToFile: arrayOfFootage) {
		fileOut << footageToFile;
	}
	fileOut.close();
}

std::vector<Footage> FileRepository::getAllFootage() {
	std::vector<Footage> allFootage;
	std::ifstream fileIn(fileName);
	Footage footage;
	while (fileIn >> footage) {
		allFootage.push_back(footage);
	}
	return allFootage;
}

Footage FileRepository::getCurrentElement() {
	std::vector<Footage> arrayOfTapes = getAllFootage();
	if (currentElement == arrayOfTapes.size()) 		currentElement = 0;
	return *(arrayOfTapes.begin() + currentElement++);
}

void FileRepository::openList() {
	std::string systemString = "open " + fileName;
	const char* openListString = systemString.c_str();
	system(openListString);
}

//void FileRepository::setPath(const std::string& newFileName) {
//	if (fileName == " ") {
//		throw std::exception();
//	}
//	std::ofstream createFileIfNotExist(fileName);
//	createFileIfNotExist.close();
//	fileName = newFileName;
//}
//


