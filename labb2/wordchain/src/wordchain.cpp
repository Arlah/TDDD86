#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

set<string> neighbour(const string& source, set<string>& dictionary) {
    set<string> list;
    int length = source.length();
    int alphabet = ALPHABET.length();

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < alphabet; j++) {
            string new_word = source;
            new_word[i] = ALPHABET[j];

            if (dictionary.find(new_word) != dictionary.end()) {
                list.insert(new_word);
                dictionary.erase(new_word);
            }
        }
    }
    return list;
}

int wordchain(string word_1, string word_2, set<string>& dictionary) {
    queue<stack<string>> chain;
    stack<string> start, current;
    start.push(word_1);
    chain.push(start);

    while (!chain.empty()) {
        current = chain.front();
        chain.pop();

        if (current.top() == word_2) {
            while (!current.empty()) {
                string next = current.top();
                current.pop();
                if (current.empty()) {
                    cout << " " << next;
                }
                else {
                    cout << " " << next << " ->";
                }

            }
            cout << " " << "\n" << endl;
            cout << "Done" << endl;
            return 0;
        }
        else {

            set<string> list = neighbour(current.top(), dictionary);
            for (set<string>::iterator it = list.begin(); it != list.end(); it++) {
            //for (int it = 0; it <= list.size()-1; it++) {
                //if (dictionary.find(word) != dictionary.end())
                    string word = *it;

                    //dictionary.erase(word);
                    stack<string> newchain = current;
                    newchain.push(word);
                    chain.push(newchain);
                //}
            }

        }
    }
    return 1;
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    std::string word_1, word_2;

    cout << "Please type two words: ";
    cin >> word_1 >> word_2;
    cout << endl;



    ifstream file ("dictionary.txt");
    set<string> dictionary;

    if (file.is_open()) {
        string temp;

        while (getline(file, temp)) {
            dictionary.insert(temp);
        }
        cout << "Dictionary created" << "\n" << endl;
        cout << " Chain from " << word_2 << " back to " << word_1 << ":" << endl;
        wordchain(word_1, word_2, dictionary);
    }
    else {
        cout << "Dictionary.txt could not be opened" << endl;
    }

    //wordchain(word_1, word_2, dictionary);



    return 0;
}
