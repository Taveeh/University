#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "List.h"

int main(){
//    testAll();
//	testAllExtended();
    auto l = List();
    l.add(12);
    l.add(2);
    l.add(3);
    auto x = l.iterator();
    assert(l.getSize() == 3);
    l.remove(12);
    assert(l.getSize() == 2);
    l.remove(3);
    assert(l.getSize() == 1);
//    std::cout<<"Finished SMM Tests!"<<std::endl;
//	system("pause");
}
