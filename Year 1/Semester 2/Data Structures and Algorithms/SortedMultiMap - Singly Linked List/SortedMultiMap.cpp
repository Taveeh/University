#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	rel = r;
	head = nullptr;
} // theta(1)

void SortedMultiMap::add(TKey c, TValue v) {
    auto currentElem = head;
    SMMNode* previous = nullptr;
	while (currentElem != nullptr and rel(currentElem->key, c) and currentElem->key != c) {
        previous = currentElem;
        currentElem = currentElem->next;
    }
    if (currentElem == nullptr) {
        if (previous == nullptr) {
            head = new SMMNode;
            head->key = c;
            head->next = nullptr;
            addList(head, v);
        }else {
            currentElem = new SMMNode;
            currentElem->next = nullptr;
            currentElem->key = c;
            addList(currentElem, v);
            previous->next = currentElem;
        }
    }else if (!rel(currentElem->key, c)){
        if (previous == nullptr) {
            auto newNode = new SMMNode;
            newNode->next = currentElem;
            newNode->key = c;
            addList(newNode, v);
            head = newNode;
        }else {
            auto newNode = new SMMNode;
            newNode->key = c;
            newNode->next = currentElem;
            addList(newNode, v);
            previous->next = newNode;
        }
    }else {
        addList(currentElem, v);
    }
} // O(n)

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> v;
	auto currentElem = head;
	while (currentElem != nullptr and currentElem->key != c) {
	    currentElem = currentElem->next;
	}
	if (currentElem == nullptr) return v;
	auto currentList = currentElem->list->head;
	while (currentList != nullptr) {
	    v.push_back(currentList->value);
	    currentList = currentList->next;
	}
	return v;
} // O(n)

bool SortedMultiMap::remove(TKey c, TValue v) {
    auto currentElem = head;
    SMMNode* previous = nullptr;
    while (currentElem != nullptr and currentElem->key != c) {
        previous = currentElem;
        currentElem = currentElem->next;
    }
    if (currentElem == nullptr) {
        return false;
    }
	bool val = true;
	if (sizeList(currentElem) > 1) {
        val = removeList(currentElem, v);
    }else {
        if (previous == nullptr) {
            val = removeList(currentElem, v);
            if (val) {
	            head = head->next;
	            delete currentElem;
            }

        } else {
            val = removeList(currentElem, v);
            if (val) {
	            previous->next = currentElem->next;
	            delete currentElem;
            }
        }

    }
    return val;
} // O(smm)


int SortedMultiMap::size() const {
	auto currentElement = head;
	int size = 0;
	while (currentElement != nullptr) {
	    size += sizeList(currentElement);
	    currentElement = currentElement->next;
	}
	return size;
} // theta(n)

bool SortedMultiMap::isEmpty() const {
	return head == nullptr;
} // theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
} // theta(1)

SortedMultiMap::~SortedMultiMap() {
    auto currentElem = head;
    SMMNode* previous;
    while (currentElem != nullptr) {
        previous = currentElem;
        currentElem = currentElem->next;
        delete previous;
    }
} //theta(smm)

void SortedMultiMap::addList(SortedMultiMap::SMMNode *node, TValue val) {
    auto newNode = new SLLNode;
    newNode->value = val;
    newNode->next = node->list->head;
    node->list->head = newNode;
    node->list->size++;
} // theta(1)

bool SortedMultiMap::removeList(SortedMultiMap::SMMNode* node, TValue val) {
    auto currentNode = node->list->head;
    SLLNode* previous = nullptr;
    while (currentNode != nullptr and currentNode->value != val) {
        previous = currentNode;
        currentNode = currentNode->next;
    }
    if (currentNode == nullptr) {
        return false;
    }
    if (previous == nullptr) {
        node->list->head = currentNode->next;
        delete currentNode;
    }else {
        previous->next = currentNode->next;
        delete currentNode;
    }
    node->list->size--;
    return true;
}// O(m), m - nr of values from a key

int SortedMultiMap::sizeList(SortedMultiMap::SMMNode* node) const{
    return node->list->size;
} // theta(1)

SortedMultiMap::IteratorSLLList SortedMultiMap::iteratorList(SortedMultiMap::SMMNode *node) {
  return SortedMultiMap::IteratorSLLList(node->list);
} // theta(1)

void SortedMultiMap::firstList(SortedMultiMap::IteratorSLLList& it) {
  it.current = it.list->head;
} // theta(1)

bool SortedMultiMap::validList(SortedMultiMap::IteratorSLLList& it) {
  return it.current != nullptr;
} // theta(1)

void SortedMultiMap::nextList(SortedMultiMap::IteratorSLLList& it) {
  it.current = it.current->next;
} // theta(1)

TValue SortedMultiMap::getCurrentList(SortedMultiMap::IteratorSLLList it) {
  return it.current->value;
}// theta(1)


/*
 *  Best case: theta(1)  - when key is the first key in map
 *  Worst case: theta(n) - key does not exist
 *  Total complexity: O(n)
 */
vector<TValue> SortedMultiMap::removeKey(TKey key) {
	vector<TValue> v;
	auto currentElem = head;
	SMMNode* prev = nullptr;
	while (currentElem != nullptr and currentElem->key != key) {
		prev = currentElem;
		currentElem = currentElem->next;
	}
	if (currentElem == nullptr) {
		return v;
	}
	auto currentList = currentElem->list->head;
	while (currentList != nullptr) {
		v.push_back(currentList->value);
		currentList = currentList->next;
	}
	if (prev == nullptr) {
		head = currentElem->next;
		delete currentElem;
	}else {
		prev->next = currentElem->next;
		delete currentElem;
	}
	return v;
}
