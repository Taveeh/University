//
// Created by Octavian Custura on 31/03/2020.
//

#include "List.h"
#include <exception>
#include <iostream>

void List::add(TValue value) {
    auto* currentNode = new SLLNode;
    currentNode->next = head;
    currentNode->val = value;
    head = currentNode;
    size++;
}

List::List() {
    head = nullptr;
    size = 0;
}

int List::getSize() const {
    return size;
}

void List::remove(TValue value) {
    if (head->val == value) {
        auto current = head;
        head = head->next;
        free(current);
        size--;
        return;
    }
    auto currentElem = head->next;
    auto previous = head;
    while (currentElem != nullptr) {
        if (currentElem->val == value) {
            previous->next = currentElem->next;
            free(currentElem);
            size--;
            return;
        }
        previous = previous->next;
        currentElem = currentElem->next;
    }
}

ListIterator List::iterator() const {
    auto it = ListIterator();
    std::cout << it.list << ' ' <<it.current;
    return it;
}

