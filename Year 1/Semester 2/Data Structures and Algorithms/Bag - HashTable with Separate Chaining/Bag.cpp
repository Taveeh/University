#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <cmath>
using namespace std;


Bag::Bag() {
	m = 10;
	sizeH = 0;
	table = new Node*[m];
	for (int i = 0; i < m; ++i) {
		table[i] = nullptr;
	}
//	h = &Bag::h;
}


void Bag::add(TElem elem) {
	if ((float)sizeH / (float)m >= ALPHA) {
		resize(2 * m);
	}
	auto poz = h(elem);
	auto newNode = new Node;
	newNode->value = elem;
	newNode->next = table[poz];
	table[poz] = newNode;
	sizeH++;
}


bool Bag::remove(TElem elem) {
	if (sizeH == 0) {
		return false;
	}
	auto current = table[h(elem)];
	Node* prev = nullptr;
	bool exists = false;
	while (current != nullptr) {
		if (current->value == elem) {
			if (prev == nullptr) {
				table[h(elem)] = current->next;
				delete current;
			}else {
				prev->next = current->next;
				delete current;
			}
			sizeH--;
			exists = true;
			break;
		}
		prev = current;
		current = current->next;
	}
	return exists;
}


bool Bag::search(TElem elem) const {
	if (sizeH == 0) {
		return false;
	}
	auto current = table[h(elem)];
	while (current != nullptr) {
		if (current->value == elem) {
			return true;
		}
		current = current->next;
	}
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	int poz = h(elem);
	auto current = table[poz];
	int occurrence = 0;
	while (current != nullptr) {
		if (current->value == elem) {
			occurrence++;
		}
		current = current->next;
	}
	return occurrence;
}


int Bag::size() const {
	return sizeH;
}


bool Bag::isEmpty() const {
	return sizeH == 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	for (int i = 0; i < m; ++i) {
		auto current = table[i];
		while (current != nullptr) {
			auto prev = current;
			current = current->next;
			delete prev;
		}
	}
	delete []table;
}

void Bag::resize(int newCap) {
	Node** newArr = new Node*[newCap];
	for (int i = 0; i < newCap; ++i) {
		newArr[i] = nullptr;
	}
	auto oldM = m;
	m = newCap;
	for (int i = 0; i < oldM; ++i) {
		auto current = table[i];
		while (current != nullptr) {
			auto prev = current;
			auto poz = h(current->value);
			Node* newNode = new Node;
			newNode->next = newArr[poz];
			newNode->value = current->value;
			newArr[poz] = newNode;
			current = current->next;
			delete prev;
		}
	}
	delete []table;
	table = newArr;
}

int Bag::h(TElem elem) const {
	return abs(elem % m);
}

