#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>

// Forward declaration of the template class BinarySearchTree
template<class DataType>
class BinarySearchTree;

template<class DataType>
class TreeNode 
{
	friend class BinarySearchTree<DataType>;

	private:
		DataType _data;
		TreeNode<DataType>* _pLeft;
		TreeNode<DataType>* _pRight;

		void left(TreeNode *node) {
			_pLeft = node;
		}

		void right(TreeNode *node) {
_pRight = node;
		}

	public:
		TreeNode() {}

		~TreeNode() {
			std::cout << "TreeNode destructor called.\n";
		}

		TreeNode(const DataType &newItem) {
			_data = newItem;
		}

		TreeNode* left() const {
			return _pLeft;
		}

		TreeNode* right() const {
			return _pRight;
		}

		const DataType& data() const {
			return _data;
		}

		DataType& data() {
			return _data;
		}

		void data(const DataType& newData) {
			_data = newData;
		}
};

template<class DataType>
class BinarySearchTree
{
private:
	std::size_t _size;
	TreeNode<DataType>* _root;

	void inOrderTraverse(TreeNode<DataType>* root, void(*itemFound)(const DataType& foundItem)) const {
		if (root != NULL) {
			inOrderTraverse(root->left(), itemFound);
			itemFound(root->data());
			inOrderTraverse(root->right(), itemFound);
		}
	}

public:

	BinarySearchTree() { }

	~BinarySearchTree() {
		std::cout << "Destructor for BinarySearchTree called.\n";
	}

	std::size_t size() const {
		return _size;
	}

	bool empty() const {
		return _root == NULL ? true : false;
	}

	void print() const {
		traverse([](const DataType& data)->void {
			std::cout << data << " ";
		});

		std::cout << "\n";
	}

	void debug(std::ostream &out) const {
		std::cout << "Debug not implemented!\n";
	}

	bool find(const DataType &searchItem, void(*foundNode)(const DataType&)) {
		std::cout << "Find not implemented!\n";
		return false;
	}

	bool erase(const DataType &deleteItem) {
		std::cout << "Erase not implemented!\n";
		return false;
	}

	void insert(const DataType &newItem) {
		if (empty()) {
			TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
			_root = node;
		}
		else {
			insertRecursive(_root, newItem);
		}
	}

	void insert(const DataType &newItem,
		void(*duplicateItemFound)(DataType &existingItem, const DataType &newItem)) {
		if (empty()) {
			TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
			_root = node;
		}
		else {
			insertRecursive(_root, newItem, duplicateItemFound);
		}

		std::cout << "Insert not implemented!\n";
	}

	TreeNode<DataType>* insertRecursive(TreeNode<DataType>* root, const DataType &newItem) {
		if (root == NULL) {
			TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
			return node;
		}

		if (newItem < root->data()) {
			root->left(insertRecursive(root->left(), newItem));
		} else if (newItem == root->data()) {
			root->data(newItem);
		} else if (newItem > root->data()) {
			root->right(insertRecursive(root->right(), newItem));
		}
	}

	TreeNode<DataType>* insertRecursive(TreeNode<DataType>* root, const DataType &newItem,
		void(*duplicateItemFound)(DataType &existingItem, const DataType &newItem)) {
		if (root == NULL) {
			TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
			return node;
		}

		if (newItem < root->data()) {
			root->left(insertRecursive(root->left(), newItem));
		}
		else if (newItem == root->data()) {
			duplicateItemFound(root->data(), newItem);
		}
		else if (newItem > root->data()) {
			root->right(insertRecursive(root->right(), newItem));
		}
	}

	void traverse(void(*itemFound)(const DataType& foundItem)) const {
		inOrderTraverse(_root, itemFound);
	}	
};


#endif /* BINARYSEARCHTREE_H_ */
