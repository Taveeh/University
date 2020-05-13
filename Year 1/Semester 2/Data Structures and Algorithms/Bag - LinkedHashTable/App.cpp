#include "Bag.h"
#include "BagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;
	Bag bag;
	for (int i = -20; i < 20; ++i) {
		if (i == 5) bag.add(5);
		bag.add(i);

	}
	BagIterator it = bag.iterator();
	it.first();
	std::cout <<std::endl << bag.size() << std::endl;
	while (it.valid()) {
		std::cout << it.getCurrent() << ' ';
		it.next();
	}
	it.first();
	std::cout << std::endl;
	while(it.valid()) {
		if (it.getCurrent() % 5 == 0) {
			assert(it.remove() % 5 == 0);
		}


//		if (it.valid()) {
			std::cout << it.getCurrent() << ' ';
			it.next();
//		}
	}
	std::cout << std::endl;
	it.first();
	std::cout <<std::endl << bag.size() << std::endl;
	while (it.valid()) {
		std::cout << it.getCurrent() << ' ';
		it.next();
	}
	std::cout << std::endl;
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