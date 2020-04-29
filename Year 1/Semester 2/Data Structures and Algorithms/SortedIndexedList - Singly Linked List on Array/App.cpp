#include <iostream>
#include "SortedIndexedList.h"
#include "ListIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
bool asc1(TComp c1, TComp c2) {
	if (c1 <= c2) {
		return true;
	} else {
		return false;
	}
}
int main(){
    testAll();
    testAllExtended();
    SortedIndexedList list(asc1);
	list.add(22);
	list.add(22);
	list.add(22);
	list.add(12);
	list.add(12);
	list.add(12);
	list.add(33);
	list.add(33);
	list.add(33);
	list.add(22);
	list.add(22);
	list.add(22);
	list.add(22);
	list.add(22);
	ListIterator it = list.iterator();
	it.first();
	std::cout << "Size: " << list.size() << std::endl;
	while (it.valid()) {
		std::cout << it.getCurrent() << ' ';
		it.next();
	}
	std::cout << std::endl;
	std::cout << "Last index of 22 is: " << list.lastIndexOf(22) << std::endl;
	std::cout << "Last index of 5 is: " << list.lastIndexOf(5) << std::endl;
	std::cout << "Last index of 12 is: " << list.lastIndexOf(12) << std::endl;
	std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}