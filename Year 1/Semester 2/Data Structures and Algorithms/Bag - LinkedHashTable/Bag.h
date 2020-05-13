#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -11111;
typedef int TElem;
class BagIterator;
#define ALPHA 0.75
class Bag;
typedef int (Bag::*HashFunction)(TElem) ;
class Bag {
private:
	struct Node {
		TElem value;
		Node* next;
		Node* nextList;
		Node* previousList;
	};
	void resize(int newCap);
//	HashFunction h;
	int sizeH;
	Node** table;
	int m;
	Node* head;
	Node* tail;
	//DO NOT CHANGE THIS PART
	friend class BagIterator;
	int h(TElem elem) const;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator();

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};
