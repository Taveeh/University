#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d), itList(nullptr){
	currentKey = map.head;
	if (currentKey != nullptr) {
		itList = SortedMultiMap::IteratorSLLList(currentKey->list);
	}
}

void SMMIterator::first(){
	currentKey = map.head;
	if (currentKey != nullptr) {
		itList = SortedMultiMap::IteratorSLLList(currentKey->list);
	}
}

void SMMIterator::next(){
	if (currentKey == nullptr) {
		throw std::exception();
	}
	SortedMultiMap::nextList(itList);
	if (!SortedMultiMap::validList(itList)) {
		currentKey = currentKey->next;
		if (currentKey != nullptr) {
			itList = SortedMultiMap::IteratorSLLList(currentKey->list);
		}
	}
}

bool SMMIterator::valid() const{
	return currentKey != nullptr;
}

TElem SMMIterator::getCurrent() const{
	if (currentKey == nullptr) {
		throw std::exception();
	}

	TValue val = SortedMultiMap::getCurrentList(itList);
	TKey key = currentKey->key;
	return {key, val};
}


