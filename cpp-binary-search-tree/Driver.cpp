#include <iostream>
#include "BinarySearchTree.h"

template<class DataType>
void PrintNode(DataType& data) {
	std::cout << " " << data << " ";
}

int main() {
	std::cout << "Hello, World!.\n";

	BinarySearchTree<int> tree;

	tree.insert(4);
	
	tree.print();
	tree.insert(1);
	tree.print();

	tree.insert(3);
	tree.insert(3);
	tree.insert(2);

	tree.print();

	//tree.traverse(&PrintNode);

	std::getchar();

	return 0;
}