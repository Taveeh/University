#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c) {
	if (bag.isEmpty()) {
		currentKey = -1;
		currentVal = nullptr;
	} else {
		currentKey = 0;
		while (currentKey < bag.m and bag.table[currentKey] == nullptr) {
			currentKey++;
		}
		currentVal = bag.table[currentKey];
	}
}

void BagIterator::first() {
	if (bag.isEmpty()) {
		throw std::exception();
	}
	currentKey = 0;
	while (bag.table[currentKey] == nullptr) {
		currentKey++;
	}
	currentVal = bag.table[currentKey];
}


void BagIterator::next() {
	if (currentKey == -1 or currentVal == nullptr) {
		throw std::exception();
	}
	currentVal = currentVal->next;
	if (currentVal == nullptr) {
		currentKey++;
		while(currentKey < bag.m and bag.table[currentKey] == nullptr) {
			currentKey++;
		}
		if (currentKey == bag.m) {
			currentKey = -1;
		}else {
			currentVal = bag.table[currentKey];
		}
	}
}


bool BagIterator::valid() const {
	return currentKey != -1 and currentVal != nullptr;
}



TElem BagIterator::getCurrent() const {
	if (currentKey == -1) {
		throw std::exception();
	}
	return currentVal->value;
}
