#include <iostream>

using namespace std;

// if you use mac, just in case your code doesn't work, do this:
// sudo xcode-select --switch /Library/Developer/CommandLineTools/

template <class T>
T& List<T>::operator[](int idx) {
    ListNode<T>* ptr = _head;
    if (idx >= _size)// note: max index is -1 from size
        cout << "Index out of bound error (operator[])" << endl;// Returns the head item if out of bound
    else {
        for (int i = 0; i < idx; i++)
            ptr = ptr->_next;
    }
    T& result = (ptr->_item);
    return result;
}

template <class T>
void List<T>::insertAtPos(int idx, T item) {
    if (idx > _size) { // note: insert is diff from operator, includes 1 more
        cout << "Index out of bound error (insertAtPos)" << endl;
        return;
    }
    ListNode<T>* aNewNode = new ListNode<T>(item);
    ListNode<T>* currentHead = _head;
    ListNode<T>* previousHead = NULL;
    for (int i = 0; i < idx; i++) {
        previousHead = currentHead;
        currentHead = currentHead->_next;
    }
    // Insert before* currentHead
    aNewNode->_next = currentHead;
    if (previousHead) { previousHead->_next = aNewNode; } else { _head = aNewNode; }
    _size++;
}

template <class T>
void List<T>::removeAtPos(int idx){
    if (idx >= _size) { // can only remove stuff inside the list
        cout << "Index out of bound error (removeAtPos)" << endl;
        return;
    }
    ListNode<T>* currentHead = _head;
    ListNode<T>* previousHead = NULL;
    for (int i = 0; i < idx; i++) {
        previousHead = currentHead;
        currentHead = currentHead->_next;
    }
    // Remove currentHead
    ListNode<T>* temp = currentHead;
    if (previousHead) { previousHead->_next = currentHead->_next; }
    else { _head = currentHead->_next; }
    delete temp;
    _size--;
}
