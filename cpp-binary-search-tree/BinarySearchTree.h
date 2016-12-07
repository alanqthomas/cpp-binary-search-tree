#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>
#include <iomanip>

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

		bool find(const DataType& value, void(*foundNode)(const DataType&)) {
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

		void debug(std::ostream &out) {
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
		out << std::endl << std::endl << "=========================" << std::endl;
		out << "*******START DEBUG*******" << std::endl;		
		out << "=========================" << std::endl << std::endl;
		_root->debug(out);
		out << std::endl << "=========================" << std::endl;
		out << "********END DEBUG********" << std::endl;
		out << "=========================" << std::endl << std::endl;
	}	

	bool find(const DataType &searchItem, void(*foundNode)(const DataType&)) {
		if (_root == NULL)
			return false;
		else
			return _root->find(searchItem, foundNode);
	}
	
	bool erase(const DataType &deleteItem) {
		DataType data = _root->data();
		_root = eraseRecursive(_root, deleteItem);

		bool erased = data == _root->data();

		if (erased)
			_size--;

		return erased;
	}

	TreeNode<DataType>* eraseRecursive(TreeNode<DataType>* root, const DataType &deleteItem) {
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

	TreeNode<DataType>* minNode(TreeNode<DataType>* root) {
		TreeNode<DataType>* cursor = root;

		while (cursor->left() != NULL)
			cursor = cursor->left();

		return cursor;
	}

	void insert(const DataType &newItem) {
		if (empty()) {
			TreeNode<DataType>* node = new TreeNode<DataType>(newItem);
			_root = node;
		}
		else {
			insertRecursive(_root, newItem);
		}

		_size++;
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

		_size++;
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
