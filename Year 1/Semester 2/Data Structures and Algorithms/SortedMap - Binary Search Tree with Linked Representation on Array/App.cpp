#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"
#include "SMIterator.h"
#include <vector>

#include <iostream>
using namespace std;

int main() {
	SortedMap map(increasing);
//	populateSMEmpty(map, 1, 10);
	std::vector<int> v = {11, 7, 20, 2, 9, 4, 19, 25, 15, 13, 17};
	for (auto i: v)
		map.add(i, i + 23);
	assert(map.getValueRange() == 23);
//	map.remove(11);
//	map.show();
//	showMap(map);
//	map.remove(15);
//	map.show();
//	showMap(map);

	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


