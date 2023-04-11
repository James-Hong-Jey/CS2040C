void HashTable::insert(int n) {
    int insert_index = -1;
    int m;
    for (int i = 0; i < _size; i++) {
        m = (h(n) + i * i) % _size;
        if (_ht[m] == 0) {
            // search is over
            insert_index = insert_index == -1 ? m : insert_index;
            break;
        }
        if(_ht[m] == n) {
            cout << n << " already exists in the hash table." << endl;
            // default output format for error message
            return;
        }
        if (insert_index == -1 && _ht[m] == -1) // ensures only the first found slot is filled
           insert_index = m;
    }
    // if it survives until here, it is not yet inserted
    insert_index = insert_index == -1 ? m : insert_index;
    _ht[insert_index] = n;
    _nItem++;
}
//n does not necesarrily exist in the hash table
void HashTable::remove(int n) {
    for (int i = 0; i < _size; i++) {
        int m = (h(n) + i * i) % _size;
        if (_ht[m] == 0) { return; }
        if (_ht[m] == n) {
            _ht[m] = -1;
            _nItem--;
            return;
        }
    }
    cout << "Fail to remove " << n << endl;
}

bool HashTable::exist(int n) {
    for (int i = 0; i < _size; i++) {
        int m = (h(n) + i * i) % _size;
        if (_ht[m] == n) { return true; }
    }
    return false;
}

void HashTable::resize(int newSize) {
    int* old_heap = _ht;
    int old_size = _size;
    _ht = new int[newSize];
    _size = newSize;
    _nItem = 0;
    for (int i = 0; i < _size; i++) {
        _ht[i] = 0;
    }
    for (int i = 0; i < old_size; i++) {
        if (old_heap[i] > 0)
            insert(old_heap[i]);
    }
    delete old_heap;
}

int n3Sum(int* arr, int size, int total)
{ // in main idk they cappin or what, they give 11 numbers but size 10
    HashTable h(size * 2);
    for (int i = 0; i < size; i++) {
        h.insert(arr[i]);
    }
    // since a computer does like 10^8 computations a second
    // for an n^2 solution to pass under a second, it must < 10^4.
    // This one has ~3000 cases, so n^2 is acceptable ish

    int combis = 0;
    for (int i = 0; i < size - 2; i++) {
        h.remove(arr[i]);
        for (int j = i + 1; j < size - 1; j++) {
            int find = total - arr[i] - arr[j];
            if (find > arr[j] && h.exist(find)) { combis++; }
            // the find > arr[j] means it'll only consider the cases when j is smaller
            // to eliminate the (1 + 2 + 7 = 10) && (1 + 7 + 2 = 10) cases
            // cus the latter case would not be considered
            // Note: this only works when no duplicates
        }
    }
    return combis;
}
