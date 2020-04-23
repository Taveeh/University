#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	rel = r;
	capacity = 10;
	elems = new TComp[capacity];
	next = new int[capacity];
	head = -1;
	sizeL = 0;
	firstEmpty = 0;
	for (int i = 0; i < capacity - 1; ++i) {
		next[i] =  i + 1;
	}
	next[capacity - 1] = -1;
}

int SortedIndexedList::size() const {
	return sizeL;
}

bool SortedIndexedList::isEmpty() const {
	return sizeL == 0;
}

TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 or i >= sizeL) {
		throw std::exception();
	}
	int currentPoz = 0;
	auto current = head;
	while (currentPoz < i) {
		currentPoz++;
		current = next[current];
	}
	if (current == -1) {
		throw std::exception();
	}
	return elems[current];
}

TComp SortedIndexedList::remove(int i) {
	auto current = head;
	if (i < 0 or i >= sizeL) {
		throw std::exception();
	}
	TComp element;
	if (i == 0) {
		sizeL--;
		element =  elems[head];
		head = next[head];
	}else {
		int currentPoz = 0;
		auto prev = current;
		while (currentPoz < i) {
			prev = current;
			current = next[current];
			currentPoz++;
		}
		firstEmpty = current;
		element = elems[current];
		next[prev] = next[current];
		sizeL--;
	}
	return element;
}

int SortedIndexedList::search(TComp e) const {
	auto current = head;
	int poz = 0;
	while (current != -1 and rel(elems[current], e) and elems[current] != e) {
		poz++;
		current = next[current];
	}
	if (current == -1) {
		return -1;
	}
	if (!rel(elems[current], e)) {
		return -1;
	}
	return poz;
}

void SortedIndexedList::add(TComp e) {
	if (firstEmpty == -1) {
		resize(capacity * 2);
	}
	if (head == -1) {
		int newPos = firstEmpty;
		elems[newPos] = e;
		firstEmpty = next[firstEmpty];
		next[newPos] = head;
		head = newPos;
		sizeL++;
		return;
	}
	auto current = head;
	int prev = -1;
	while (current != -1 and rel(elems[current], e)) {
		prev = current;
		current = next[current];
	}
	if (current == -1) {
		if (prev != -1) {
			int newPos = firstEmpty;
			firstEmpty = next[firstEmpty];
			next[prev] = newPos;
			next[newPos] = -1;
			elems[newPos] = e;
			sizeL++;
		}
	} else {
		if (prev == -1) {
			int newPos = firstEmpty;
			firstEmpty = next[firstEmpty];
			elems[newPos] = e;
			next[newPos] = head;
			head = newPos;
			sizeL++;
		} else {
			int newPos = firstEmpty;
			firstEmpty = next[firstEmpty];
			elems[newPos] = e;
			next[prev] = newPos;
			next[newPos] = current;
			sizeL++;
		}
	}

}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	delete []elems;
	delete []next;
}

void SortedIndexedList::resize(int newCap) {
//	capacity = newCap;
	auto* newElems = new TComp [newCap];
	int* newNext = new int[newCap];
	for (int i = 0; i < capacity; ++i) {
		newElems[i] = elems[i];
		newNext[i] = next[i];
	}
	for (int i = capacity; i < newCap - 1; ++i) {
		newNext[i] = i + 1;
	}
	newNext[newCap - 1] = -1;
	delete[] elems;
	delete[] next;
	elems = newElems;
	next = newNext;
	firstEmpty = capacity;
	capacity = newCap;

}
