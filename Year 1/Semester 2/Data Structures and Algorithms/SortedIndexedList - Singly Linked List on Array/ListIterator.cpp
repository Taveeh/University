#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	currentElement = list.head;
} // theta(1)

void ListIterator::first(){
	currentElement = list.head;
} // theta(1)

void ListIterator::next(){
	if (currentElement == -1) {
		throw std::exception();
	}
	currentElement = list.next[currentElement];
} //theta(1)

bool ListIterator::valid() const{
	return currentElement != -1;
} //theta(1)

TComp ListIterator::getCurrent() const{
	if (currentElement == -1) {
		throw std::exception();
	}
	return list.elems[currentElement];
} //theta(1)


