//
// Created by Octavian Custura on 20/06/2020.
//

#ifndef FINALEXAM_REPOSITORY_H
#define FINALEXAM_REPOSITORY_H
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>
#include <pthread.h>
class Exception: public std::exception {
private:
	std::string message;
public:
	explicit Exception(std::string message) : message(std::move(message)) {}
	const char* what() {
		return message.c_str();
	}
};
template <class T>
class Repository {
private:
	std::string fileName;
	std::vector<T> readFile() const;
	void writeFile(std::vector<T> toWrite);
	std::mutex mymutex;

public:
	explicit Repository(std::string  fileName) : fileName(std::move(fileName)) {}
	Repository(Repository const &repo) {
		fileName = repo.fileName;
	}
	void addElement(T element);
	void updateElement(T element);
	void removeElement(T element);
	std::vector<T> getAllElements() const;
};

template<class T>
std::vector<T> Repository<T>::readFile() const {
	std::vector<T> array;
	std::ifstream fin(fileName);
	std::string elementString;
	std::getline(fin, elementString);
	T elem{};
	while(!elementString.empty()) {
		std::stringstream stringToElement(elementString);
		stringToElement >> elem;
		array.push_back(elem);
		elementString.clear();
		std::getline(fin, elementString);
	}
	fin.close();
	return array;
}

template<class T>
void Repository<T>::writeFile(std::vector<T> toWrite) {
	std::sort(toWrite.begin(), toWrite.end(), [](T a, T b) {
		return a.getConstellation() > b.getConstellation();
	});
	std::ofstream fout(fileName);
	for (const auto& elem: toWrite) {
		fout << elem << std::endl;
	}
	fout.close();
}

template<class T>
void Repository<T>::addElement(T element) {

	/*
	 * Function that adds an element
	 * Input:
	 *  T - element
	 * Throws:
	 *  Exception - if element already exists
	 */
//	std::cout << std::endl << element << std::endl;
	mymutex.lock();
	std::vector<T> elements = readFile();
//	std::cout << "Size in addElement = " << elements.size() << std::endl;
	for (const auto& elem: elements) {
//		std::cout << elem;
		if (elem == element) {
			mymutex.unlock();
			throw Exception("Duplicate element");
		}
	}
	mymutex.unlock();
	elements.push_back(element);
	mymutex.lock();
	writeFile(elements);
	mymutex.unlock();

}

template<class T>
void Repository<T>::updateElement(T element) {
	mymutex.lock();
	auto elements = readFile();
	for (auto& elem: elements) {
		if (elem == element) {
			elem = element;
			writeFile(elements);
			mymutex.unlock();
			return;
		}
	}
	mymutex.unlock();
	throw Exception("Element does not exist");
}

template<class T>
void Repository<T>::removeElement(T element) {
	auto elements = readFile();
	auto elementToRemove = std::find_if(elements.begin(), elements.end(), [element](T elem) {
		return elem == element;
	});
	if (elementToRemove == elements.end()) {
		throw Exception("Element does not exist");
	}
	elements.erase(elementToRemove);
	writeFile(elements);
}

template<class T>
std::vector<T> Repository<T>::getAllElements() const {
	return readFile();
}
#endif //FINALEXAM_REPOSITORY_H
