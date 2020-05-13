#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(Bag& c): bag(c) {
	currentElem = bag.head;
} // theta(1)

void BagIterator::first() {
	if (bag.isEmpty()) {
		throw std::exception();
	}

	currentElem = bag.head;
} // theta(1)


void BagIterator::next() {

	if (currentElem == nullptr) {
		throw std::exception();
	}
	currentElem = currentElem->nextList;
} // theta(1)


bool BagIterator::valid() const {
	return currentElem != nullptr;
} // theta(1)




TElem BagIterator::getCurrent() const {
	if (currentElem == nullptr) {
		throw std::exception();
	}
	return currentElem->value;
} // theta(1)

TElem BagIterator::remove() {
	if (currentElem == nullptr) {
		throw std::exception();
	}
	auto current = bag.table[bag.h(currentElem->value)];
	auto oldCurrentElem = currentElem;
	currentElem = currentElem->nextList;

	Bag::Node* prev = nullptr;
	while (current != oldCurrentElem) {
		prev = current;
		current = current->next;
	}
	if (current == bag.head) {
		if (current == bag.tail) {
			bag.head = nullptr;
			bag.tail = nullptr;
		}else {
			bag.head = bag.head->nextList;
			bag.head->previousList = nullptr;
		}
	}else if (current == bag.tail) {
		bag.tail = current->previousList;
		bag.tail->nextList = nullptr;
	}else {
		current->previousList->nextList = current->nextList;
		current->nextList->previousList = current->previousList;
		current->nextList = nullptr;
		current->previousList = nullptr;
	}
//	current->previousList->nextList = current->nextList;
//	current->nextList->previousList = current->previousList;

	if (prev == nullptr) {
		bag.table[bag.h(current->value)]->next = current->next;
	}else {
		prev->next = current->next;
	}

	auto value = current->value;
	bag.sizeH--;
	delete current;
	return value;



}