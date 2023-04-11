#pragma once

#ifndef SIMPLELINKEDLISTTEMPLATEHPP
#define SIMPLELINKEDLISTTEMPLATEHPP

#include <iostream>
#include "simpleLinkedListTemplate.h"
using namespace std;


template <class T>
ListNode<T>::ListNode(T n)
{
	_item = n;
	_next = NULL;
}

template <class T>
void List<T>::insertHead(T n)
{
	ListNode<T> *aNewNode = new ListNode<T>(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

template <class T>
void List<T>::removeHead()
{
	if (_size > 0) {
		ListNode<T> *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

template <class T>
void List<T>::print(bool withNL) {

	ListNode<T> *temp = _head;
	while (temp) {
		cout << temp->_item;
		if (withNL)
			cout << endl;
		else
			cout << " ";
		temp = temp->_next;
	}
	cout << endl;
	  
}

template <class T>
bool List<T>::exist(T n) {
	ListNode<T>* now = _head;
	for(; now; now = now->_next) {
		if(now->_item == n){
			return true;
		}
	}
	return false; 
}


template <class T>
T List<T>::headItem()
{
	if (_size)
		return *_head;
}

template <class T>
T List<T>::extractMax()
{
	if(!_head) {return T();}
	// Find Max
	ListNode<T>* now = _head;
	ListNode<T>* max = _head;
	ListNode<T>* before = _head; // lags behind by 1 
	for(; now->_next; now = now->_next) {
		if(now->_next->_item > max->_item) {
			max = now->_next;
			before = now;
		}
	}

	// Delete the max
	if(max == _head) {
		_head = max -> _next;
	} else if (max-> _next == NULL) {
		before -> _next = NULL;
	} else {
		before -> _next = max -> _next;
	}
	T result = max -> _item;
	delete max;
	_size--;

	// Lastly, return the saved T result
	return result;
}

template <class T>
void List<T>::reverseOp() {
	ListNode<T>* now = _head;
	ListNode<T>* before = NULL;
	ListNode<T>* after = NULL;

	while(now -> _next != NULL) {
		after = now -> _next;
		now -> _next = before;
		before = now;
		now = after;
	}
	now -> _next = before;
	_head = now;
}

template <class T>
List<T>::~List()
{
	while (_head)
		removeHead();
};


#endif