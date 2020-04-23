#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	currentElement = list.head;
}

void ListIterator::first(){
	currentElement = list.head;
}

void ListIterator::next(){
	if (currentElement == -1) {
		throw std::exception();
	}
	currentElement = list.next[currentElement];
}

bool ListIterator::valid() const{
	return currentElement != -1;
}

TComp ListIterator::getCurrent() const{
	if (currentElement == -1) {
		throw std::exception();
	}
	return list.elems[currentElement];
}


