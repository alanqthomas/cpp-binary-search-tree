#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>
#include <iomanip>

// Forward declaration of the template class BinarySearchTree
template<class DataType>
class BinarySearchTree;

// Class representing a node in a BST
template<class DataType>
class TreeNode 
{
	friend class BinarySearchTree<DataType>;

	private:
		// Data contained in this node
		DataType _data;
		// Pointer to left child
		TreeNode<DataType>* _pLeft;
		// Pointer to right child
		TreeNode<DataType>* _pRight;

		// Set left child
		void left(TreeNode *node) {
			_pLeft = node;
		}

		// Set the right child
		void right(TreeNode *node) {
			_pRight = node;
		}

	public:
		// Default constructor
		TreeNode() {}

		//Default destructor
		~TreeNode() {
			std::cout << "TreeNode destructor called.\n";
		}

		// Constructor that initializes the node's data
		TreeNode(const DataType &newItem) {
			_data = newItem;
		}

		// Get the left child
		TreeNode* left() const {
			return _pLeft;
		}

		// Get the right child
		TreeNode* right() const {
			return _pRight;
		}

		// Get an immutable reference to data
		const DataType& data() const {
			return _data;
		}

		// Get a mutable reference to data
		DataType& data() {
			return _data;
		}

		// Set the data of the node
		void data(const DataType& newData) {
			_data = newData;
		}

		// Print debug information for this node
		void debug(std::ostream &out);

		// Find the specified data in this node and all children
		bool TreeNode<DataType>::find(const DataType& value, void(*foundNode)(const DataType&));
};

// Class representing a binary search tree
template<class DataType>
class BinarySearchTree
{
private:
	// Size of this tree
	std::size_t _size;
	// Reference to the root of this tree
	TreeNode<DataType>* _root;

public:
	// Default constructor
	BinarySearchTree() { }

	// Default destructor
	~BinarySearchTree() {
		std::cout << "Destructor for BinarySearchTree called.\n";
	}

	// Return the size of the tree
	std::size_t size() const {
		return _size;
	}

	// Return whether the tree is empty or not
	bool empty() const {
		return _root == NULL ? true : false;
	}

	// Traverse the tree and call the passed-in function for each node
	void inOrderTraverse(TreeNode<DataType>* root, void(*itemFound)(const DataType& foundItem)) const;

	// Print the tree
	void print() const;

	// Print debug information for the tree
	void debug(std::ostream &out) const;

	// Search the tree for the specified node and call the function if found
	// Return true if found, false otherwise
	bool find(const DataType &searchItem, void(*foundNode)(const DataType&));
	
	// Try to erase the given item. Return true if found, false otherwise.
	bool erase(const DataType &deleteItem);

	// Recursive implementation for erase
	TreeNode<DataType>* eraseRecursive(TreeNode<DataType>* root, const DataType &deleteItem);

	// Find the minimum node in the given tree/sub tree
	TreeNode<DataType>* minNode(TreeNode<DataType>* root);

	// Insert the new item into the tree
	void insert(const DataType &newItem);

	// Insert the new item into the tree. Call the passed-in function if the item exists already
	void insert(const DataType &newItem, void(*duplicateItemFound)(DataType &existingItem, const DataType &newItem));

	// Recursive implementation for insert
	TreeNode<DataType>* insertRecursive(TreeNode<DataType>* root, const DataType &newItem);

	// Recursive implementation for insert
	TreeNode<DataType>* insertRecursive(TreeNode<DataType>* root, const DataType &newItem,
		void(*duplicateItemFound)(DataType &existingItem, const DataType &newItem));

	// Go through the tree and invoke the passed-in function on each node
	void traverse(void(*itemFound)(const DataType& foundItem)) const {
		inOrderTraverse(_root, itemFound);
	}	
};

template<class DataType>
void BinarySearchTree<DataType>::traverse(void(*itemFound)(const DataType& foundItem)) const {
	inOrderTraverse(_root, itemFound);
}

template<class DataType>
TreeNode<DataType>* BinarySearchTree<DataType>::insertRecursive(TreeNode<DataType>* root, const DataType &newItem,
	void(*duplicateItemFound)(DataType &existingItem, const DataType &newItem)) {
	if (root == NULL) {
		TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
		return node;
	}

	if (newItem < root->data())
		root->left(insertRecursive(root->left(), newItem, duplicateItemFound));
	else if (newItem == root->data())
		duplicateItemFound(root->data(), newItem);
	else if (newItem > root->data())
		root->right(insertRecursive(root->right(), newItem, duplicateItemFound));
}

template<class DataType>
TreeNode<DataType>* BinarySearchTree<DataType>::insertRecursive(TreeNode<DataType>* root, const DataType &newItem) {
	if (root == NULL) {
		TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
		return node;
	}

	if (newItem < root->data())
		root->left(insertRecursive(root->left(), newItem));
	else if (newItem == root->data())
		root->data(newItem);
	else if (newItem > root->data())
		root->right(insertRecursive(root->right(), newItem));
}

template<class DataType>
void BinarySearchTree<DataType>::insert(const DataType &newItem,
	void(*duplicateItemFound)(DataType &existingItem, const DataType &newItem)) {
	if (empty()) {
		TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
		_root = node;
	}
	else {
		insertRecursive(_root, newItem, duplicateItemFound);
	}

	_size++;
}

template<class DataType>
void BinarySearchTree<DataType>::insert(const DataType &newItem) {
	if (empty()) {
		TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
		_root = node;
	}
	else {
		insertRecursive(_root, newItem);
	}

	_size++;
}

template<class DataType>
TreeNode<DataType>* BinarySearchTree<DataType>::minNode(TreeNode<DataType>* root) {
	TreeNode<DataType>* cursor = root;

	while (cursor->left() != NULL)
		cursor = cursor->left();

	return cursor;
}

template<class DataType>
TreeNode<DataType>* BinarySearchTree<DataType>::eraseRecursive(TreeNode<DataType>* root, const DataType &deleteItem) {
	if (root == NULL)
		return root;

	if (deleteItem < root->data()) {
		root->left(eraseRecursive(root->left(), deleteItem));
	}
	else if (deleteItem > root->data()) {
		root->right(eraseRecursive(root->right(), deleteItem));
	}
	else {
		if (root->left() == NULL) {
			TreeNode<DataType>* child = root->right();
			delete root;
			return child;
		}
		else if (root->right() == NULL) {
			TreeNode<DataType>* child = root->left();
			delete root;
			return child;
		}

		TreeNode<DataType>* child = minNode(root->right());
		root->data(child->data());
		root->right(eraseRecursive(root->right(), child->data()));
	}
}

template<class DataType>
bool BinarySearchTree<DataType>::erase(const DataType &deleteItem) {
	DataType data = _root->data();
	_root = eraseRecursive(_root, deleteItem);

	bool erased = data == _root->data();

	if (erased)
		_size--;

	return erased;
}

template<class DataType>
bool BinarySearchTree<DataType>::find(const DataType &searchItem, void(*foundNode)(const DataType&)) {
	if (_root == NULL)
		return false;
	else
		return _root->find(searchItem, foundNode);
}

// Traverse the binary search tree in an in-order manner
template<class DataType>
void BinarySearchTree<DataType>::inOrderTraverse(TreeNode<DataType>* root, void(*itemFound)(const DataType& foundItem)) const {
	if (root != NULL) {
		BinarySearchTree::inOrderTraverse(root->left(), itemFound);
		itemFound(root->data());
		BinarySearchTree::inOrderTraverse(root->right(), itemFound);
	}
}

// Prints all nodes in this BST
template<class DataType>
void BinarySearchTree<DataType>::print() const {
	std::cout << "Printing tree of words in order:" << std::endl;
	traverse([](const DataType& data)->void {
		std::cout << data << std::endl;
	});

	std::cout << "Finished printing tree of words" << std::endl << std::endl;
}

// Prints debug information for this tree
template<class DataType>
void BinarySearchTree<DataType>::debug(std::ostream &out) const {
	out << std::endl << std::endl << "=========================" << std::endl;
	out << "*******START DEBUG*******" << std::endl;
	out << "=========================" << std::endl << std::endl;
	/*traverse([](const TreeNode<DataType>& node)->void {
		node.debug(std::cout);
		std::cout << std::endl;
	});*/
	traverse([](const DataType& data)->void {
		std::cout << data << std::endl;
	});
	out << std::endl << "=========================" << std::endl;
	out << "********END DEBUG********" << std::endl;
	out << "=========================" << std::endl << std::endl;
}

template<class DataType>
void TreeNode<DataType>::debug(std::ostream &out) {
	out << "address=[" << this << "]" << std::endl;
	out << "data=" << _data << std::endl;
	out << "left=[" << _pLeft << "]" << std::endl;
	out << "right=[" << _pRight << "]" << std::endl;
	out << "=========================" << std::endl;

	if (_pLeft != NULL)
		_pLeft->debug(out);

	if (_pRight != NULL)
		_pRight->debug(out);
}

template<class DataType>
bool TreeNode<DataType>::find(const DataType& value, void(*foundNode)(const DataType&)) {
	if (value == this->data()) {
		foundNode(this->data());
		return true;
	}
	else if (value < this->data()) {
		if (_pLeft == NULL)
			return false;
		else
			return _pLeft->find(value, foundNode);
	}
	else if (value > this->data()) {
		if (_pRight == NULL)
			return false;
		else
			return _pRight->find(value, foundNode);
	}

	return false;
}

#endif /* BINARYSEARCHTREE_H_ */
