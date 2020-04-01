#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	rel = r;
	head = nullptr;
}

void SortedMultiMap::add(TKey c, TValue v) {
	TElem elem = TElem(c, v);

}

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	return vector<TValue>();
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
    return false;
}


int SortedMultiMap::size() const {
	//TODO - Implementation
	return 0;
}

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return false;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
}

//void SortedMultiMap::addAfter(SortedMultiMap::SLLNode *node, TElem elem) {
//    auto* newNode = new SLLNode;
//    newNode->info = elem;
//    newNode->next = node->next;
//    node->next = newNode;
//}

