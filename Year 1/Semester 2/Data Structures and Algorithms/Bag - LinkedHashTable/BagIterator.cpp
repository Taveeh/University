#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c) {
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
