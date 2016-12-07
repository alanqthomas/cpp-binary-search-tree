#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
#include "Word.h"

using namespace std;

int main() {
	BinarySearchTree<Word> tree;

	ifstream file;
	file.open("abc.txt");
	char output[1000];

	if (file.is_open()) {
		while (!file.eof()) {			
			file >> output;
			string* newWord = new string(output);
			Word* w = new Word(*newWord);
			cout << w << endl;
			tree.insert(*w);
			//cout << output << endl;
		}
	}
	file.close();

	tree.print();	
	std::getchar();

	return 0;
}