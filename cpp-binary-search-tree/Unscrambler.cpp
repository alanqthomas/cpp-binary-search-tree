#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
#include "Word.h"

using namespace std;

// Since we found a duplicate key, we just want to add the word
// to the existing node
void duplicateItemFound(Word &existingItem, const Word &newItem) {
	//cout << "Duplicate found. Adding word to existing key: " << existingItem.key() << "." << endl;
	Word* w = new Word();
	w->key(existingItem.key());
	w->words(existingItem.words());	
	w->insert(newItem.words()[0]);	
	existingItem = *w;
}

// Print the list of words associated with this item/key
void itemFound(const Word& word) {
	word.listWords();
}

int main() {
	// Create the tree
	BinarySearchTree<Word> tree;

	// Open a file stream
	ifstream file;
	file.open("english_words.txt");
	// Reserve a buffer
	char output[1000];

	// It'll take a while to load that many words
	cout << "Loading words..." << endl;

	// While there is more input, create a Word object
	// and insert it into the tree.
	if (file.is_open()) {
		while (!file.eof()) {			
			file >> output;
			string* newWord = new string(output);
			Word* w = new Word(*newWord);
			tree.insert(*w, duplicateItemFound);
		}
	}
	file.close();

	cout << "Finished loading words." << endl << endl;

	// Create an input buffer
	char buffer[100];

	// Main program loop
	while (true) {
		// Request user input
		cout << "Enter a scrambled word: ";
		cin >> buffer;

		// Create a word object from the input
		string* newWord = new string(buffer);
		Word* w = new Word(*newWord);

		// See if we can find the object and call the appropriate function if we do.
		bool found = tree.find(*w, itemFound);

		if (!found)
			cout << "Could not unscramble that word! Try another one." << endl;
	}

	return 0;
}