//
// Created by Octavian Custura on 01/04/2020.
//

#ifndef SORTEDMULTIMAP_LISTITERATOR_H
#define SORTEDMULTIMAP_LISTITERATOR_H

#include "List.h"

class ListIterator {
    friend class List;
private:
    const List& list;
    explicit ListIterator(const List& list1);
    List::SLLNode* current;
public:
    void first();
    void next();
    bool valid();
    TValue getCurrent();
};


#endif //SORTEDMULTIMAP_LISTITERATOR_H
