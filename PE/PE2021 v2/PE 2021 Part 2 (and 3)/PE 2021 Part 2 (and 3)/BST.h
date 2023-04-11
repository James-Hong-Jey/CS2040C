#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	int _height;
	T _sst; // sum of the all the nodes in its subtree with itself as the root
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0;  _sst = x; };

	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
private:
	bool _balancing; 
	// true: the tree will be balanced as an AVL tree mentioned in our lecture
	// false: the tree will not do any rotation to balance itself

	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withSST);
	void _preOrderPrint(TreeNode<T>*);
	void _inOrderPrint(TreeNode<T>*);
	void _postOrderPrint(TreeNode<T>*);
	TreeNode<T>* _insert(TreeNode<T>* current, T x);
    void _destroySubTree(TreeNode<T>*);

	int _updateHeight(TreeNode<T>* node);
	int _updateSST(TreeNode<T>* node);



public:
	BinarySearchTree(bool balancing=true) { _root = NULL; _size = 0; _balancing = balancing; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withSST = true); 
	// if withSST==true, it will print the sum of subtree also

	TreeNode<T>* _leftRotation(TreeNode<T>* node);
	TreeNode<T>* _rightRotation(TreeNode<T>* node);
	int _updateBalance(TreeNode<T>* current);
	void updateHeight();
	void updateSST();

	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();

	T sumLE(T n);

	
};


template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node) {
	TreeNode<T>* brother = node->_right;
	node->_right = brother->_left;
	brother->_left = node;
	// Returns the "root" to the parent
	return brother;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node) {
	TreeNode<T>* brother = node->_left;
	node->_left = brother->_right;
	brother->_right = node;
	return brother;
}

// left - right so 1 = left heavy, 0 = balanced, -1 = right heavy, 
template <class T>
int BinarySearchTree<T>::_updateBalance(TreeNode<T>* current) {
	
	int h_left = current->_left == NULL ? -1 : current->_left->_height;
	int h_right = current->_right == NULL ? -1 : current->_right->_height;
	int diff = h_left - h_right;	
	return diff;
}

template <class T>
void BinarySearchTree<T>::updateHeight() {
	_updateHeight(_root);
}

template <class T>
int BinarySearchTree<T>::_updateHeight(TreeNode<T>* node) {
	int leftHeight = node->_left == NULL ? -1 : _updateHeight(node->_left);
	int rightHeight = node->_right == NULL ? -1 : _updateHeight(node->_right);
	int finalHeight = leftHeight >= rightHeight ? leftHeight : rightHeight;
	finalHeight++;
	node->_height = finalHeight;

	// For sst
	int leftSST = node->_left == NULL ? 0 : node->_left->_sst;
	int rightSST = node->_right == NULL ? 0 : node->_right->_sst;
	node->_sst = leftSST + rightSST;

	return finalHeight;
}

template <class T>
void BinarySearchTree<T>::updateSST() {
	_updateSST(_root);
}

template <class T>
int BinarySearchTree<T>::_updateSST(TreeNode<T>* node) {
	// For sst
	int leftSST = node->_left == NULL ? 0 : _updateSST(node->_left);
	int rightSST = node->_right == NULL ? 0 : _updateSST(node->_right);
	node->_sst = leftSST + rightSST + node->_item;
	return leftSST + rightSST + node->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {
	/*
	// Iterative insert
	// Can improve this by adding a balance factor, and not caring about height
	// because certain rotation types are deterministic
	TreeNode<T>* parent = NULL;
	while (1) {
		if (current->_item > x)
		{
			if (current->_left) {
				parent = current;
				current = current->_left;
			}
			else
			{
				current->_left = new TreeNode<T>(x);
				_size++;
				break;
			}
		}
		else if (x > current->_item) {
			if (current->_right) {
				parent = current;
				current = current->_right;
			}
			else
			{
				current->_right = new TreeNode<T>(x);
				_size++;
				break;
			}
		}
	}
	current = parent;
	*/

	if (current->_item > x)
	{
		if (current->_left)
			current->_left = _insert(current->_left, x);
		else
		{
			current->_left = new TreeNode<T>(x);
			_size++;
		}
	}
	else if (x > current->_item) {
		if (current->_right)
			current->_right = _insert(current->_right, x);
		else
		{
			current->_right = new TreeNode<T>(x);
			_size++;
		}
	}
	else
		return current; 


	if (_balancing) {
		updateHeight();
		// check balance
		int diff = _updateBalance(current);
		if (diff * diff > 1) { // need to balance
			if (diff >= 2) { // LEFT HEAVY
				// if left child is right heavy, need to go left then left rotate first, then right rotate
				if (_updateBalance(current->_left) < 0) { // CHILD RIGHT HEAVY
					current->_left = _leftRotation(current->_left);
				}
				// else, just right rotate straight
				current = _rightRotation(current);
			}
			else if (diff <= -2) { // RIGHT HEAVY
				// if right child is left heavy, need to go right, then right rotate first, then left rotate
				if (_updateBalance(current->_right) > 0) { // CHILD LEFT HEAVY
					current->_right = _rightRotation(current->_right);
				}
				// Then left rotate normally
				current = _leftRotation(current);
			}
			//updateSST();
		}
	}
	return current;
}

template <class T>
void BinarySearchTree<T>::insert(T x) {

	if (_root == NULL)
	{
		_root = new TreeNode<T>(x);
		_size++;
	}
	else
		_root = _insert(_root, x);

}




template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}

template <class T>
T BinarySearchTree<T>::sumLE(T n)
{
	updateSST();
	TreeNode<T>* node = _root;
	T sum = node->_sst;
	 do {
		if (n == node->_item) {
			if (node->_right)
				sum -= node->_right->_sst;
			// cut off right side then end
			break;
		} else if (n > node->_item) {
			if(node->_right){ // traverse right
				node = node->_right;
				continue;
			}
			// no nodes left to search: end
			break;
		} else { // n < node->_item
			if (node->_left) { // traverse left
				// cut off everything on right parent
				sum -= node->_sst - node->_left->_sst;
				node = node->_left;
				continue;
			}
			// everything is bigger
			sum = 0;
			break;
		}
	 } while (true);

	return sum;
}



template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << "(" << node->_sst << ") ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}

template <class T>
void BinarySearchTree<T>::preOrderPrint() {
	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}



template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << "(" << node->_sst << ") ";
}

template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_inOrderPrint(node->_left);
	cout << node->_item,
	_inOrderPrint(node->_right);
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withSST) {

	if (withSST)
		updateSST();

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withSST);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withSST)
		cout <<  "(s=" << node->_sst << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withSST);


};


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



class MagicalPancakeGym {
private:
	BinarySearchTree<long long int> s; // with balancing by default, can add (false)
	long long int total = 0;
public:
	void addPancake(long long int weight);
	long long int minimalBottomPancake2Lift(long long int totalW);
	void printPancakes();
	long long int totalWeightAbovePancake(long long int w);
};

long long int MagicalPancakeGym::totalWeightAbovePancake(long long int w)
{
	return (w - s.sumLE(w-1));
}

void MagicalPancakeGym::addPancake(long long int weight)
{
	s.insert(weight);
	total += weight;
}

void MagicalPancakeGym::printPancakes()
{
	s.inOrderPrint();
}

long long int MagicalPancakeGym::minimalBottomPancake2Lift(long long int totalW)
{
	//TreeNode<long long int>* node;
	return 0;
}

