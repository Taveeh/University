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
            currentElem->key = 0;
            addList(currentElem, v);
            previous->next = currentElem;
        }
    }else if (!rel(currentElem->key, c)){
        if (previous == nullptr) {
            auto newNode = new SMMNode;
            newNode->next = currentElem;
            newNode->key = c;
            addList(newNode, v);
            head = currentElem;
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
}

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
}

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
    if (sizeList(currentElem) > 1) {
        removeList(currentElem, v);
    }else {
        if (previous == nullptr) {
            removeList(currentElem, v);
            head = head->next;
            delete currentElem;
        } else {
            removeList(currentElem, v);
            previous->next = currentElem->next;
            delete currentElem;
        }

    }
    return true;

}


int SortedMultiMap::size() const {
	auto currentElement = head;
	int size = 0;
	while (currentElement != nullptr) {
	    size += sizeList(currentElement);
	    currentElement = currentElement->next;
	}
	return size;
}

bool SortedMultiMap::isEmpty() const {
	return head == nullptr;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    auto currentElem = head;
    SMMNode* previous;
    while (currentElem != nullptr) {
        previous = currentElem;
        currentElem = currentElem->next;
        delete previous->list;
        delete previous;
    }
}

void SortedMultiMap::addList(SortedMultiMap::SMMNode *node, TValue val) {
    auto newNode = new SLLNode;
    newNode->value = val;
    newNode->next = node->list->head;
    node->list->head = newNode;
    node->list->size++;
}

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
}

int SortedMultiMap::sizeList(SortedMultiMap::SMMNode* node) const{
    return node->list->size;
}

SortedMultiMap::IteratorSLLList SortedMultiMap::iteratorList(SortedMultiMap::SMMNode *node) {
  return SortedMultiMap::IteratorSLLList(node->list);
}

void SortedMultiMap::firstList(SortedMultiMap::IteratorSLLList& it) {
  it.current = it.list->head;
}

bool SortedMultiMap::validList(SortedMultiMap::IteratorSLLList& it) {
  return it.current != nullptr;
}

void SortedMultiMap::nextList(SortedMultiMap::IteratorSLLList& it) {
  if (it.current == nullptr) {
    throw std::exception();
  }
  it.current = it.current->next;
}

TValue SortedMultiMap::getCurrentList(SortedMultiMap::IteratorSLLList &it) {
  return it.current->value;
}
