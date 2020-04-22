//
// Created by Octavian Custura on 12/04/2020.
//

#include "MemoryRepository.h"
MemoryRepository::MemoryRepository(): currentElement(0) {
	arrayOfTapes = std::vector<Footage>();
}

void MemoryRepository::addFootage(const Footage &newFootage) {
	for (auto & arrayOfTape : arrayOfTapes) {
		if (arrayOfTape.getTitle() == newFootage.getTitle()) {
			throw RepositoryException("Duplicate Footage");
		}
	}
	arrayOfTapes.push_back(newFootage);
}

void MemoryRepository::deleteFootage(const std::string &titleToBeRemoved) {
	for (auto iteratorRepository = arrayOfTapes.begin(); iteratorRepository != arrayOfTapes.end(); ++iteratorRepository) {
		if (iteratorRepository->getTitle() == titleToBeRemoved) {
			arrayOfTapes.erase(iteratorRepository);
			return;
		}
	}
	throw RepositoryException("Footage does not exist");
}

void MemoryRepository::updateFootage(const Footage &newFootage) {
	for (auto & arrayOfTape : arrayOfTapes) {
		if (arrayOfTape.getTitle() == newFootage.getTitle()) {
			arrayOfTape = newFootage;
			return;
		}
	}
	throw RepositoryException("Footage does not exist");}

std::vector<Footage> MemoryRepository::getAllFootage() {
	auto arrayOfFootage = std::vector<Footage>();
	for (auto & arrayOfTape : arrayOfTapes) {
		arrayOfFootage.push_back(arrayOfTape);
	}
	return arrayOfFootage;
}

Footage MemoryRepository::getCurrentElement() {
	if (currentElement == arrayOfTapes.size()) {
		currentElement = 0;
	}
	return *(arrayOfTapes.begin() + currentElement++);
}

