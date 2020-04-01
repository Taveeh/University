//
// Created by Octavian Custura on 31/03/2020.
//

#ifndef SORTEDMULTIMAP_LIST_H
#define SORTEDMULTIMAP_LIST_H

#include "ListIterator.h"
#include "SortedMultiMap.h"

typedef int TValue;
#define NULL_TVALUE -11111

class ListIterator;

class List {
    friend class ListIterator;
private:
    struct SLLNode {
        TValue val;
        SLLNode *next;
    };
    SLLNode* head;
    int size;
public:

    explicit List();

    void add(TValue value);

    void remove(TValue value);

    int getSize() const;

    ListIterator iterator() const;

};



#endif //SORTEDMULTIMAP_LIST_H
