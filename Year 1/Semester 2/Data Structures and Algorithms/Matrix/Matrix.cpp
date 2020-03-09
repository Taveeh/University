#include "Matrix.h"
#include <exception>
#include <iostream>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    lines = nrLines;
    cols = nrCols;
    array = new Triple [5];
}

int Matrix::nrLines() const {
	return lines;
}

int Matrix::nrColumns() const {
	return cols;
}

TElem Matrix::element(int i, int j) const {
	if (i >= lines or j >= cols or i < 0 or j < 0) {
        throw exception();
    }
    std::pair<int, bool> rez = secventialSearch(make_pair(make_pair(i, j), NULL_TELEM));
	if (rez.second) {
	    return array[rez.first].second;
	}
	return NULL_TELEM;
}

void Matrix::insertElement(Triple x, int poz) {
    if (size == capacity) {
        resize(2 * capacity);
    }

    for (int i = size; i >= poz; --i) {
        array[i] = array[i - 1];
    }
    size++;
    array[poz] = x;

}

void Matrix::removeElement(int poz) {
    if (size == capacity / 4) {
        resize(capacity / 4);
    }
    for (int i = poz; i < size; ++i) {
        array[i] = array[i + 1];
    }
    --size;

}

void Matrix::resize(int val) {

    Triple *aux;
    aux  = new Triple [val];
    for (int i = 0; i < val; ++i) {
        aux[i] = array[i];
    }
    delete [] array;
    array = aux;
    capacity = val;

}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i > lines or j > cols or i < 0 or j < 0) {
        throw exception();
    }
    if (e != 0) {
        if (size == 0) {
            ++size;
            array[0] = make_pair(make_pair(i, j), e);
            return e;
        }else {
            std::pair<int, bool> rez = secventialSearch(make_pair(make_pair(i, j), e));
            if (rez.second) {
                array[rez.first].second = e;
            }else {
                insertElement(make_pair(make_pair(i, j), e), rez.first);
            }
        }
    }else {
        if (size == 0) {
            return e;
        }else {
            std::pair<int, bool> rez = secventialSearch(make_pair(make_pair(i, j), e));
            if (!rez.second) {
                return e;
            }else {
                removeElement(rez.first);
            }
        }
    }
	return NULL_TELEM;
}

std::pair<int, bool> Matrix::secventialSearch(Triple elem) const {
    for (int i = 0; i < size; ++i) {
        if (elem.first == array[i].first) {
            return make_pair(i, true);
        }
        if (elem.first < array[i].first) {
            return make_pair(i, false);
        }
    }
    return make_pair(size, false);
}


