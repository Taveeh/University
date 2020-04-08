#include <assert.h>
#include "Matrix.h"
#include <iostream>>

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
//	for (int i = 0; i < m.nrLines(); ++i) {
//	    for (int j = 0; j < m.nrColumns(); ++j) {
//	        cout << i << ' ' << j << ' ' << m.element(i, j) << '\n';
//	    }
//	}
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
}