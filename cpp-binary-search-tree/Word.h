#ifndef WORD_H_
#define WORD_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Class representing a key and it's corresponding words.
class Word {
	private:
		// The key representing this node
		string _key;
		// A list of words associated with this key
		vector<string> _words;
	public:
		//Default constructor
		Word() {}

		// Copy constructor
		Word(string word) {
			_words.push_back(word);

			string* key = new string(word);

			//cout << "key=" << *key;
			transform(key->begin(), key->end(), key->begin(), tolower);
			//cout << "->" << *key;
			sort(key->begin(), key->end());
			//cout << "->" << *key << endl;
			_key = *key;
		}

		// Default destructor
		~Word() {
			cout << "Word destructor called." << endl;
		}

		// Set the key
		void key(string k) {
			_key = k;
		}

		// Return the key 
		string key() const{
			return _key;
		}

		// Set the list of words
		void words(vector<string> w) {
			_words = w;
		}

		// Gets the list of words
		vector<string> words() const {
			return _words;
		}

		// Insert a new word into the words list
		void insert(string word) {
			string* newWord = new string(word);
			_words.push_back(*newWord);
		}

		// Prints all the words associated
		void listWords() const{
			for (int i = 0; i < _words.size(); i++)
				cout << _words[i] << " ";			
			cout << endl;
		}

		// == overload
		bool operator==(const Word& w) const {
			return _key.compare(w.key()) == 0;
		}

		// != overload
		bool operator!=(const Word& w) const {
			return _key.compare(w.key()) != 0;
		}

		// < overload
		bool operator<(const Word& w) const {
			return _key.compare(w.key()) < 0;
		}

		// <= overload
		bool operator<=(const Word& w) const {
			return _key.compare(w.key()) <= 0;
		}

		// > overload
		bool operator>(const Word& w) const {
			return _key.compare(w.key()) > 0;
		}

		// >= overload
		bool operator>=(const Word& w) const {
			return _key.compare(w.key()) >= 0;
		}
};

// << overload
std::ostream & operator<<(std::ostream & out, const Word & word)
{
	out << "[" << word.key() << ":";
	for (int i = 0; i < word.words().size(); i++) {
		out << word.words().at(i);
		if (i < word.words().size()-1)
			out << ",";
	}
	out << "]";

	return out;
}

#endif /* WORD_H_ */
