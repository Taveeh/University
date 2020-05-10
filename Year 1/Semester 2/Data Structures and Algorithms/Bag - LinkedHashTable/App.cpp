#include "Bag.h"
#include "BagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;
//	Bag bag;
//	for (int i = 0; i < 10; ++i) {
//		bag.add(i);
//	}
//	BagIterator it = bag.iterator();
//	it.first();
//	std::cout <<std::endl << bag.size() << std::endl;
//	while (it.valid()) {
//		std::cout << it.getCurrent() << ' ';
//		it.next();
//	}
//	for (int i = -10; i < 20; ++i) {
//		bag.add(i);
//	}
//	it.first();
//	std::cout << bag.size() << std::endl;
//	while (it.valid()) {
//		std::cout << it.getCurrent() << ' ';
//		it.next();
//	}
	testAllExtended();

	cout << "All test over" << endl;
}