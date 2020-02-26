#include "Matrix.h"
#include <exception>
#include <iostream>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    lines = nrLines;
    cols = nrCols;
    array = new Triple [2];
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
	for (int poz = 0; poz < size; ++poz) {
	    if (array[poz].first.first == i and array[poz].first.second == j) {
	        return array[poz].second;
	    }
	}
	return NULL_TELEM;
}
void Matrix::insertElement(Triple x, int poz) {
    size++;

    for (int i = size - 2; i >= poz; --i) {
        array[i + 1] = array[i];
    }

    array[poz] = x;
    if (size == capacity) {
        resize(2 * capacity);
    }
}

void Matrix::removeElement(int poz) {
    for (int i = poz + 1; i < size; ++i) {
        array[i - 1] = array[i];
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
        }
        for (int poz = 0; poz < size; ++poz) {
            if (i == array[poz].first.first and j == array[poz].first.second) {
                array[poz].second = e;
                break;
            }
            if ((i == array[poz].first.first and j > array[poz].first.second) or i > array[poz].first.first) {
                insertElement(make_pair(make_pair(i, j), e), poz);
                break;
            }
        }
    }else {
        if (size == 0) {
            return NULL_TELEM;
        }else {
            if (element(i, j) == 0) {
                return NULL_TELEM;
            }else {
                for (int poz = 0; poz < size; ++poz) {
                    if (i == array[poz].first.first and j == array[poz].first.second) {
                        removeElement(poz);
                        return NULL_TELEM;
                    }
                }
            }
        }
    }

	return NULL_TELEM;
}


