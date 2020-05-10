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
	head = nullptr;
	tail = nullptr;
//	h = &Bag::h;
} //theta(m)


void Bag::add(TElem elem) {
	if ((float)sizeH / (float)m >= ALPHA) {
		resize(2 * m);
	}
	auto poz = h(elem);
	auto newNode = new Node;
	newNode->value = elem;
	newNode->next = table[poz];
	newNode->nextList = nullptr;
	newNode->previousList = tail;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}else {
		tail->nextList = newNode;
		tail = newNode;
	}
	table[poz] = newNode;
	sizeH++;
} // theta(1)


bool Bag::remove(TElem elem) {
	if (sizeH == 0) {
		return false;
	}
	auto current = table[h(elem)];
	Node* prev = nullptr;
	while (current != nullptr and current->value != elem) {
		prev = current;
		current = current->next;
	}
	if (current == nullptr) {
		return false;
	}
	if (prev == nullptr) {
		table[h(elem)] = current->next;
		if (current == head) {
			if (current == tail) {
				head = nullptr;
				tail = nullptr;
			}else {
				head = head->nextList;
				head->previousList = nullptr;
			}
		}else if (current == tail) {
			tail = current->previousList;
			tail->nextList = nullptr;
		}else {
			current->previousList->nextList = current->nextList;
			current->nextList->previousList = current->previousList;
			current->nextList = nullptr;
			current->previousList = nullptr;
		}
		delete current;
	}else {
		if (current == head) {
			if (current == tail) {
				head = nullptr;
				tail = nullptr;
			}else {
				head = head->nextList;
				head->previousList = nullptr;
			}
		}else if (current == tail) {
			tail = current->previousList;
			tail->nextList = nullptr;
		}else {
			current->previousList->nextList = current->nextList;
			current->nextList->previousList = current->previousList;
			current->nextList = nullptr;
			current->previousList = nullptr;
		}
		prev->next = current->next;
		delete current;
	}
	sizeH--;
	return true;
} // O(n)


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
} // O(n)

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
 // O(n)

int Bag::size() const {
	return sizeH;
} // theta(1)


bool Bag::isEmpty() const {
	return head == nullptr;
} // theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
} // theta(1)


Bag::~Bag() {
//	for (int i = 0; i < m; ++i) {
//		auto current = table[i];
//		while (current != nullptr) {
//			auto prev = current;
//			current = current->next;
//			delete prev;
//		}
//	}
	auto current = head;
	while (current != nullptr) {
		auto prev = current;
		current = current->nextList;
		delete prev;
	}
	delete []table;
} // theta(n)

void Bag::resize(int newCap) {
	Node* oldHead = head;
	head = nullptr;
	tail = nullptr;
	delete []table;
	m = newCap;
	table = new Node*[m];
	for (int i = 0; i < m; ++i) {
		table[i] = nullptr;
	}
	auto current = oldHead;
	sizeH = 0;
	while (current != nullptr) {
		auto prev = current;
		add(current->value);
		current = current->nextList;
		delete prev;
	}
} // theta(m)

int Bag::h(TElem elem) const {
	return abs(elem) % m;
} // theta(1)

