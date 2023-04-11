#include <iostream>
#include "circularIntLinkedList.h"
using namespace std;

ListNode::ListNode(int n)
{
	_item = n;
	_next = NULL;
}


////////////////////////////////////////////////////////////////////////////
//      You should ONLY modify the bodies of the following functions      //
// You should copy and paste ALL the functions below onto coursemology    //
////////////////////////////////////////////////////////////////////////////

void CircularList::advanceHead()
{
	if (_size < 2) { return; }
	_head = _head->_next;
}

void CircularList::insertHead(int n)
{
	if (_size == 0) {
		ListNode* newNode = new ListNode(n);
		_head = newNode;
		_head->_next = _head;
		_size++;
		return;
	}
	ListNode* newNode = new ListNode(_head->_item);
	
	// Static head strategy - head position stays same, items swapped
	// 1. Steal _head's _next
	newNode->_next = _head->_next;
	// 2. Point _head->_next to newNode
	_head->_next = newNode;
	// 3. Swap items
	_head->_item = n;

	_size++;
};

void CircularList::removeHead()
{
	// modify this
	if (_size == 0) { return; }
	// 1. _head copies contents of _head->_next
	_head->_item = _head->_next->_item;
	// 2. _head points to _head->_next->_next
	ListNode* temp = _head->_next;
	_head->_next = _head->_next->_next;
	// 3. Delete _head->_next
	delete temp;
	_size--;
}

void CircularList::print() {
	if (_size == 0) { 
		cout << endl;
		return; 
	}
	ListNode* current = _head;
	cout << current->_item << " ";
	for (int i = 1; i < _size; i++) {
		current = current->_next;
		cout << current->_item << " ";
	}
	cout << endl;
}

bool CircularList::exist(int n) {
	if (_size == 0) { return false; }
	ListNode* current = _head;
	for (int i = 0; i <= _size; i++) {
		current = current->_next;
		if (current->_item == n) { return true; }
	}
	return false;
}

int CircularList::headItem()
{
	// Qn assumes non-empty
	return _head->_item;
}

CircularList::~CircularList()
{
	while (_size > 0)
		removeHead();
};

