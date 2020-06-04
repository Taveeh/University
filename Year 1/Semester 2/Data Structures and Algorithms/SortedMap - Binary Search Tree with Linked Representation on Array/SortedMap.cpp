#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SortedMap::SortedMap(Relation r) {
	rel = r;
	capacity = 10;
	elems = new TElem[capacity];
	left = new int[capacity];
	right = new int[capacity];
	next = new int[capacity];
	parent = new int[capacity];
	root = -1;
	firstEmpty = 0;
	mapSize = 0;
	for (int i = 0; i < capacity - 1; ++i) {
		next[i] = i + 1;
		left[i] = -1;
		right[i] = -1;
		parent[i] = -1;
	}
	next[capacity - 1] = -1;
	left[capacity - 1] = -1;
	right[capacity - 1] = -1;
	parent[capacity - 1] = -1;
} // theta(1)

TValue SortedMap::add(TKey k, TValue v) {
	if (firstEmpty == -1) {
		resize(capacity * 2);
	}
//	cout << "Map size: " << mapSize << endl;
	if (mapSize == 0) {
		root = firstEmpty;
		elems[root] = std::make_pair(k, v);
		firstEmpty = next[firstEmpty];
		mapSize++;
		return NULL_TVALUE;
	}
	auto currentNode = root;
	auto prevNode = root;
	while (currentNode != -1 and elems[currentNode].first != k) {
		prevNode = currentNode;
		if (rel(elems[currentNode].first, k)) {
			currentNode = right[currentNode];
		}else {
			currentNode = left[currentNode];
		}
	}
	if (currentNode != -1) {
		auto oldValue = elems[currentNode].second;
		elems[currentNode].second = v;
		return oldValue;
	} else {
		int nextPos = firstEmpty;
//		cout << "Add key " << k << " with value " << v << " on position " << nextPos << endl;
//		cout << elems[parent[prevNode]].first << " <-> " << k << endl;
		firstEmpty = next[firstEmpty];
		if (rel(elems[prevNode].first, k)) {
			right[prevNode] = nextPos;
			elems[nextPos] = std::make_pair(k, v);
			parent[nextPos] = prevNode;
		}else {
			left[prevNode] = nextPos;
			elems[nextPos] = std::make_pair(k, v);
			parent[nextPos] = prevNode;
		}
		mapSize++;
		return NULL_TVALUE;
	}
} // O(n)

TValue SortedMap::search(TKey k) const {
	if (mapSize == 0) {
		return NULL_TVALUE;
	}
	auto currentNode = root;
	while (currentNode != -1) {
		if (elems[currentNode].first == k) {
			return elems[currentNode].second;
		}
		if (rel(elems[currentNode].first, k)) {
			currentNode = right[currentNode];
		}else {
			currentNode = left[currentNode];
		}
	}
	return NULL_TVALUE;
} // O(n)

TValue SortedMap::remove(TKey k) {
	if (root == -1) {
		return NULL_TVALUE;
	}
	if (mapSize == 1) {
		if (elems[root].first == k) {
			auto oldValue = elems[root].second;
			root = -1;
			mapSize--;
			return oldValue;
		}else return NULL_TVALUE;
	}
	auto currentNode = root;
	auto prevNode = -1;
	while (currentNode != -1 and elems[currentNode].first != k) {
		prevNode = currentNode;
		if (rel(elems[currentNode].first, k)) {
			currentNode = right[currentNode];
		}else {
			currentNode = left[currentNode];
		}
	}
	if (currentNode == -1) {
		return NULL_TVALUE;
	}
	int nrKids = 0;
	int child = -1;
	if (left[currentNode] != -1) {
		child = left[currentNode];
		nrKids++;
	}
	if (right[currentNode] != -1) {
		child = right[currentNode];
		nrKids++;
	}
	auto oldValue = elems[currentNode].second;
	mapSize--;
	switch (nrKids) {
		case 0:
//			std::cout << "Remove key " << k << " with 0 descendants" << endl;
			if (left[prevNode] == currentNode) {
				left[prevNode] = -1;
			}else {
				right[prevNode] = -1;
			}
			next[currentNode] = firstEmpty;
			firstEmpty = currentNode;
			return oldValue;
		case 1:
//			std::cout << "Remove key " << k << " with 1 descendant" <<endl;
			if (root == currentNode) {
				root = child;
			} else if (left[prevNode] == currentNode) {
				if (left[currentNode] != -1) {
					left[prevNode] = left[currentNode];
					parent[left[currentNode]] = prevNode;
				}else {
					left[prevNode] = right[currentNode];
					parent[right[currentNode]] = prevNode;

				}
			}else {
				if (left[currentNode] != -1) {
					right[prevNode] = left[currentNode];
					parent[left[currentNode]] = prevNode;

				}else {
					right[prevNode] = right[currentNode];
					parent[right[currentNode]] = prevNode;

				}
			}
			next[currentNode] = firstEmpty;
			firstEmpty = currentNode;
			return oldValue;
		case 2: {
			auto nextElem = minFromThere(right[currentNode]);
			std::cout << "Remove key " << k << " and replace it with key " << elems[nextElem].first << endl;
			elems[currentNode] = elems[nextElem];
			next[currentNode] = firstEmpty;
			firstEmpty = currentNode;

			if (right[nextElem] != -1) {
				parent[right[nextElem]] = parent[nextElem];
				right[nextElem] = -1;
			}
			left[parent[nextElem]] = right[nextElem];
			parent[nextElem] = -1;
			right[nextElem] = right[currentNode];
			left[nextElem] = left[currentNode];
			return oldValue;
		}
		default:
			break;
	}
	return NULL_TVALUE;
} // O(n)

int SortedMap::size() const {
	return mapSize;
} // theta(1)

bool SortedMap::isEmpty() const {
	return mapSize == 0;
} // theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
} // theta(1)

SortedMap::~SortedMap() {
	delete []elems;
	delete []left;
	delete []right;
	delete []parent;
	delete []next;
} // theta(1)

void SortedMap::resize(int newCap) {
	auto* newElems = new TElem[newCap];
	int* newLeft = new int[newCap];
	int* newRight = new int[newCap];
	int* newParent = new int[newCap];
	int* newNext = new int[newCap];
	for (int i = 0;i < capacity; ++i) {
		newElems[i] = elems[i];
		newNext[i] = next[i];
		newLeft[i] = left[i];
		newRight[i] = right[i];
		newParent[i] = parent[i];
	}
	for (int i = capacity; i < newCap - 1; ++i) {
		newNext[i] = i + 1;
		newLeft[i] = -1;
		newRight[i] = -1;
		newParent[i] = -1;
	}
	newNext[newCap - 1] = -1;
	newLeft[newCap - 1] = -1;
	newRight[newCap - 1] = -1;
	newParent[newCap - 1] = -1;
	delete []elems;
	delete []next;
	delete []left;
	delete []right;
	delete []parent;
	elems = newElems;
	next = newNext;
	parent = newParent;
	left = newLeft;
	right = newRight;
	firstEmpty = capacity;
	capacity = newCap;
} //theta(n)

int SortedMap::minFromThere(int node) {
	if (node == -1) {
		return -1;
	}
	while (left[node] != -1) {
		node = left[node];
	}
	return node;
} // O(n)

int SortedMap::maxFromThere(int node) {
	if (node == -1) {
		return -1;
	}
	while(right[node] != -1) {
		node = right[node];
	}
	return node;
}

int SortedMap::getValueRange() {
	/*
	 * Complexity: theta(n)
	 */
	if (mapSize == 0) {
		return -1;
	}
	int min = -NULL_TVALUE, max = NULL_TVALUE;
	inorderTraversal(root, min, max);
	return max - min;
}

void SortedMap::inorderTraversal(int node, int& min, int& max) {
	if (node != -1) {
		inorderTraversal(left[node], min, max);
		if (elems[node].second > max) {
			max = elems[node].second;
		}
		if (elems[node].second < min) {
			min = elems[node].second;
		}
		inorderTraversal(right[node], min, max);
	}
}
//void SortedMap::show() {
//	std::cout << "Root: " << root <<  " ---- " << " Size: " << mapSize << endl;
//	for (int i = 0; i < capacity; ++i) {
//		std::cout << "Key: " << elems[i].first << " Value: " << elems[i].second << " Left: " << left[i] << " Right: " << right[i] << " Parent: " << parent[i] << " Next: " << next[i] << std::endl;
//	}
//}
