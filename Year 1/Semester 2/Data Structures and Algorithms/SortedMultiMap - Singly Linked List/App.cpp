#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedMultiMap.h"
#include "SMMIterator.h"
bool desc1(TKey c1, TKey c2) {
	if (c1 >= c2) {
		return true;
	} else {
		return false;
	}
}

int main(){
    testAll();
	testAllExtended();
	SortedMultiMap smm = SortedMultiMap(desc1);
	int kMin = 0;
	int kMax = 10;
	for (int i = kMin; i <= kMax; i++) {
		smm.add(i, i + 1);
		smm.add(i, i + 2);
	}
	assert(smm.removeKey(10000).size() == 0);
	for (int i = kMin; i <= kMax; ++i) {
		assert(smm.removeKey(i).size() == 2);
	}
	for (int i = kMin; i <= kMax; ++i) {
		assert(smm.search(i).size() == 0);
	}
	std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
