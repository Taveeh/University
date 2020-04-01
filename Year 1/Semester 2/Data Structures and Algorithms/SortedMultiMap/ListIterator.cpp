//
// Created by Octavian Custura on 01/04/2020.
//

#include "ListIterator.h"


ListIterator::ListIterator(const List &list1):list(list1) {
    current = list.head;
}

void ListIterator::first() {
    current = list.head;
}

void ListIterator::next() {
    current = current->next;
}

bool ListIterator::valid() {
    return current != nullptr;
}

TValue ListIterator::getCurrent() {
    return current->val;
}