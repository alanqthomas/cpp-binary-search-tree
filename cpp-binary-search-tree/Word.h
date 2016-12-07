#ifndef WORD_H_
#define WORD_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Word {
	private:
		string _key;
		vector<string> _words;
	public:
		Word() {}

		Word(string word) {
			_words.push_back(word);
			_key = word;
		}

		~Word() {
			cout << "Word destructor called." << endl;
		}

		string key() const{
			return _key;
		}

		vector<string> words() const {
			return _words;
		}

		void insert(string word) {
			_words.push_back(word);
		}

		bool operator==(const Word& w) const {
			return _key.compare(w.key()) == 0;
		}

		bool operator!=(const Word& w) const {
			return _key.compare(w.key()) != 0;
		}

		bool operator<(const Word& w) const {
			return _key.compare(w.key()) < 0;
		}

		bool operator<=(const Word& w) const {
			return _key.compare(w.key()) <= 0;
		}

		bool operator>(const Word& w) const {
			return _key.compare(w.key()) > 0;
		}

		bool operator>=(const Word& w) const {
			return _key.compare(w.key()) >= 0;
		}
};

std::ostream & operator<<(std::ostream & out, const Word & word)
{
	for (int i = 0; i < word.words().size(); i++) {
		out << word.words().at(i) << " ";
	}

	return out;
}

#endif /* WORD_H_ */
