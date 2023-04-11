

template <class T>
void DHeap<T>::_bubbleUp(int index) {
    int parent_index = abs( (index - 1) / _d );
    if (_heap[parent_index] < _heap[index]) {
        T temp = _heap[parent_index];
        _heap[parent_index] = _heap[index];
        _heap[index] = temp;
        _bubbleUp(parent_index);
    }
}

template <class T>
void DHeap<T>::_bubbleDown(int index) {
    int child_index = _d * index;
    int max_index = index;
    for (int i = 0; i < _d; i++) {
        child_index++;
        if (child_index < _n && _heap[child_index] > _heap[max_index])
            max_index = child_index;
    }
    if (max_index == index) { return; }
    T temp = _heap[max_index];
    _heap[max_index] = _heap[index];
    _heap[index] = temp;
    _bubbleDown(max_index);
}

template <class T>
T DHeap<T>::extractMax() {
    T result = peekMax();
    _heap[0] = _heap[_n - 1];
    _n--;
    _bubbleDown(0);
    return result;
}


template <class T>
void DHeap<T>::insert(T item) {
    _heap[_n] = item;
    _bubbleUp(_n);
    _n++;
}
