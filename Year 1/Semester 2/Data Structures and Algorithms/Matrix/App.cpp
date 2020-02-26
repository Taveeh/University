
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {


	testAll();
	testAllExtended();
//    Matrix m(4, 4);
//    cout << m.element(0, 0);
//    m.modify(0, 0, 2);
//    cout << m.element(0, 0);
	cout << "Test End" << endl;
	system("pause");
}