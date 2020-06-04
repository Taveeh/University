#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	firstNode = map.root;
	if (firstNode != -1) {
		while (map.left[firstNode] != -1) {
			firstNode = map.left[firstNode];
		}
	}
	currentNode = firstNode;
} //O(n)

void SMIterator::first(){
	currentNode = firstNode;
} //theta(1)

void SMIterator::next(){
	if (currentNode == -1) {
		throw std::exception();
	}
	if (map.right[currentNode] != -1) {
		currentNode = map.right[currentNode];
		while (map.left[currentNode] != -1) {
			currentNode = map.left[currentNode];
		}
	}else {
		while (map.parent[currentNode] != -1 and map.right[map.parent[currentNode]] == currentNode) {
			currentNode = map.parent[currentNode];
		}
		currentNode = map.parent[currentNode];
	}
} // O(n)

bool SMIterator::valid() const{
	return currentNode != -1;
} // theta(1)

TElem SMIterator::getCurrent() const{
	if (currentNode == -1) {
		throw std::exception();
	}
	return map.elems[currentNode];
} // theta(1)


