#pragma once
#include "heap.h"
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
T return_max(T a, T b) { // just to test
	return a > b ? a : b;
}

template <class T>
void Heap<T>::_bubbleUp(int index) {
	if(index == 0) {return;}
	int parent = (index - 1) / 2;
	if(_heap[index] > _heap[parent]) {
		// Swap
		T temp = _heap[parent];
		_heap[parent] = _heap[index];
		_heap[index] = temp;
		_bubbleUp(parent);
	}
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
	if(index * 2 + 1 >= _n) {return;} // no children -> leaf
	int left_child = index * 2 + 1;
	int right_child = index * 2 + 2;
	T test = return_max(_heap[left_child], _heap[right_child]);
	T current = _heap[index];
	if(_heap[left_child] > current && _heap[left_child] > _heap[right_child]) {
		// If a. right child doesn't exist
		// b. left child violates && is the bigger child
		T temp = _heap[left_child];
		_heap[left_child] = _heap[index];
		_heap[index] = temp;
		_bubbleDown(left_child);
	} else if (_heap[right_child] > current) {
		// if right child violates && is the bigger child 
		T temp = _heap[right_child];
		_heap[right_child] = _heap[index];
		_heap[index] = temp;
		_bubbleDown(right_child);
	}
}

template <class T>
void Heap<T>::insert(T item) {
	// I think _n is the size of array?
	// So I think can naively just treat as position
	_heap[_n] = item;
	_bubbleUp(_n);
	_n++;
}

template <class T>
T Heap<T>::extractMax() {
	T result = _heap[0];
	_heap[0] = _heap[_n - 1];
	_n--;
	_bubbleDown(0);
	return result;
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++)
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x)
            return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{
	int from_index = _lookFor(from);
	_heap[from_index] = to;
	_bubbleDown(from_index);
}


template <class T>
void Heap<T>::increaseKey(T from, T to)
{
	int from_index = _lookFor(from);
	_heap[from_index] = to;
	_bubbleUp(from_index);
}

template <class T>
void Heap<T>::deleteItem(T x)
{
	int index = _lookFor(x);
	_heap[index] = _heap[0] + 1;
	_bubbleUp(index);
	extractMax();
}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}

}






#endif
