#include <iostream>
#include "BinarySearchTree.h"

template<class DataType>
void PrintNode(DataType& data) {
	std::cout << " " << data << " ";
}

int main() {
	std::cout << "Hello, World!.\n";

	BinarySearchTree<int> tree;

	tree.insert(50);
	tree.insert(70);
	tree.insert(80);
	tree.insert(60);
	tree.insert(30);
	tree.insert(20);
	tree.insert(40);
	tree.print();

	tree.erase(90);
	tree.erase(100);
	tree.erase(70);
	tree.print();

	bool found = tree.find(70, [](const int& data)->void {
		std::cout << "Found the value " << data << ".\n";
	});

	std::cout << "Found=" << found << ".\n";

	//tree.traverse(&PrintNode);

	std::getchar();

	return 0;
}