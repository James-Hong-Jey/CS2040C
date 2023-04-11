#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode;


template <class T>
class TreeNode{
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	TreeNode<T>* _parent;
	int _height;
	int _balance;
public:
	TreeNode(T x, TreeNode<T>* parent = NULL) { _left = _right = NULL; _item = x; _height = 0; _balance = 0; _parent = parent; };
	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree{
protected:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeight);

	// The following functions are optional for you to implement. 
	TreeNode<T>* _insert(TreeNode<T>* current, T x);
	//void _insert(TreeNode<T>* current, T x);
	void _inOrderPrint(TreeNode<T>*);
	void _postOrderPrint(TreeNode<T>*);
	void _preOrderPrint(TreeNode<T>*);
	int _updateHeight(TreeNode<T>*, TreeNode<T>*);
	TreeNode<T>* _updateBalance(TreeNode<T>*);
	TreeNode<T>* _rightRotation(TreeNode<T>*);
	TreeNode<T>* _leftRotation(TreeNode<T>*);
	TreeNode<T>* _searchMax(TreeNode<T>*);
	TreeNode<T>* _searchMin(TreeNode<T>*);
	TreeNode<T>* _search(TreeNode<T>*, T);
	void _destroySubTree(TreeNode<T>*);

public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	void updateHeight();
	T searchMax(); 
	T searchMin();
	bool exist(T x);
	T search(T x) { return T(); };
	T successor(T);

	void checkBalance(TreeNode<T>*);

};

template <class T>
void BinarySearchTree<T>::insert(T x)
{
	_root = _root ? _insert(_root, x) : new TreeNode<T>(x);
	if (_size == 0) _size++;
	updateHeight();
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {

	if (current->_item > x)
	{
		if (current->_left)
			current->_left = _insert(current->_left, x);
		else
		{
			current->_left = new TreeNode<T>(x,current);
			_size++;
		}
	}
	else if (x > current->_item) {
		if (current->_right)
			current->_right = _insert(current->_right, x);
		else
		{
			current->_right = new TreeNode<T>(x,current);
			_size++;
		}
	}
	else
		return current; // When the node already existed in the tree

	updateHeight();
	return _updateBalance(current);

}

template <class T>
void BinarySearchTree<T>::updateHeight() {
	// cout << "I have cometh" << endl;
	_updateHeight(_root, NULL);
}

template <class T>
int BinarySearchTree<T>::_updateHeight(TreeNode<T>* node, TreeNode<T>* parent){
	node->_parent = parent; // Updates the parents too
	int leftHeight = node->_left == NULL ? -1 : _updateHeight(node->_left, node);
	int rightHeight = node->_right == NULL ? -1 : _updateHeight(node->_right, node);
	int finalHeight = leftHeight >= rightHeight ? leftHeight : rightHeight;
	finalHeight++;
	node->_height = finalHeight;
	node->_balance = leftHeight - rightHeight;
	return finalHeight;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node){
	TreeNode<T>* brother = node->_right;
	node->_right = brother->_left;
	brother->_left = node;

	// Returns the "root" to the parent
	return brother;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node){
	TreeNode<T>* brother = node->_left;
	node->_left = brother->_right;
	brother->_right = node;

	return brother;
}

	// left - right so 1 = left heavy, 0 = balanced, -1 = right heavy, 
template <class T>
TreeNode<T>* BinarySearchTree<T>::_updateBalance(TreeNode<T>* node) {

	if(node->_balance >= 2) { // LEFT HEAVY
		// if left child is right heavy, need to go left then left rotate first, then right rotate
		if(node->_left->_balance < 0) { // CHILD RIGHT HEAVY
			node->_left = _leftRotation(node->_left);
		}
		// else, just right rotate straight
		return _rightRotation(node);
	} else if (node->_balance <= -2) { // RIGHT HEAVY
		// if right child is left heavy, need to go right, then right rotate first, then left rotate
		if(node->_right->_balance > 0) { // CHILD LEFT HEAVY
			node->_right = _rightRotation(node->_right);
		}
		// Then left rotate normally
		return _leftRotation(node);
	}
	// Else, it is balanced
	return node;
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeight) {
	if (!node) {
		return;
	}

	if (node->_right) {
		_printTree(indent + 2, node->_right, withHeight);
	}

	for (int i = 0; i < indent; i++) {
		cout << "  ";
	}

	cout << node->_item;
	if (withHeight) {
		cout << "(h=" << node->_height << ")";
	}

	cout << endl;
	if (node->_left) {
		_printTree(indent + 2, node->_left, withHeight);
	}
}

template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}


template <class T>
void BinarySearchTree<T>::preOrderPrint() {

	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
	if (_root)
		_destroySubTree(_root);
}



template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
	// Recurse left, then return
	if(node -> _left)
		_inOrderPrint(node -> _left);
	// Print itself
	cout << node -> _item << " ";
	// Recurse right, then return
	if(node -> _right)
		_inOrderPrint(node -> _right);
	// Return
	return;
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}

template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
	// Recurse left 
	if(node -> _left)
		_postOrderPrint(node -> _left);
	// Recurse right, then return
	if(node -> _right)
		_postOrderPrint(node -> _right);
	// Print itself
	cout << node->_item << " ";
	// Return
	return;
}



template<class T>
T BinarySearchTree<T>::searchMin() {
	TreeNode<T>* node = _searchMin(_root);
	return node->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* node) {
	if (node->_left) {
		return _searchMin(node->_left);
	}
	return node;
}

template<class T>
T BinarySearchTree<T>::searchMax() {
	TreeNode<T>* node = _searchMax(_root);
	return node->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* node) {
	if(node->_right) {
		return _searchMax(node->_right);
	}
	return node;
}

template <class T>
bool BinarySearchTree<T>::exist(T x){
	TreeNode<T>* node = _search(_root,x);
	if(node != NULL) {
		return true;
	}
	return false;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_search(TreeNode<T>* node, T x) {
	// Check itself
	if(node->_item == x) {
		return node;
	}
	if(node->_item > x && node->_left) {
		return _search(node->_left,x);
	}
	if(node->_item < x && node->_right) {
		return _search(node->_right,x);
	}
	return NULL;
}

template <class T>
T BinarySearchTree<T>::successor(T x){
	TreeNode<T>* node = _root;
	while(node->_item != x){
		if(node->_item > x && node->_left) { 
			node = node->_left;
		} else if(node->_item < x && node->_right) {
			node = node->_right;
		} else if(node->_item > x) { // not inside, and overshot
			return node->_item;
		} else { 
			break; // meaning not inside
		}
	}

	// Finds through parents
	TreeNode<T>* parent = node->_parent;
	if(node->_right) { // Simple part - search right child
		TreeNode<T>* succ = _searchMin(node->_right);
		return succ->_item;
	} else {
		while(parent->_item < x) { // Finds the first parent that's bigger
			if(parent == _root){ // Reset if there are no right parents
				return node->_item;
			}
			parent = parent->_parent;
		}
		return parent->_item;
	}
}
