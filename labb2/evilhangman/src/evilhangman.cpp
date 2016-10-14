-#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


void curGameStatus(int guesses, vector<char>& unkWord, set<string>& words, char debug) {

    for (int i = 0; i < unkWord.size(); i++) {
        cout << " " << unkWord[i] << " ";
    }
    cout << "\n" << endl;

    cout << "You have " << guesses << " guesses left" << endl;

    if (debug == 'y') {
        cout << "Words left: " << words.size()  << endl;
    }

    return;
}

char nextGuess(set<char>& guessedChars) {

    cout << "Enter your guess: ";
    char newChar;

    while (true) {
        cin >> newChar;
        if (newChar >= 'a' && newChar <= 'z') {
            if (guessedChars.find(newChar) == guessedChars.end()) {
                guessedChars.insert(newChar);
                break;
            }
            else {
                cout << "Already tried letter, choose a new one: ";
            }
        }
        else
        {
            cout << "Enter a lowercase english character" << endl;
        }
    }

    cout << endl;
    return newChar;
}

void updateCurWords(char newGuess, set<string>& words, vector<char>& unkWord) {

    int reuseLetter = -1;
    int maxIndex, maxSize = -1;
    map<int, set<string>> partitions;
    int word_l = words.begin() -> length();

    for (int i = 0; i < unkWord.size(); i++) {
        if (unkWord[i] == newGuess) {
            reuseLetter = i;
        }
    }

    for (set<string>::iterator itr = words.begin(); itr != words.end(); itr++) {
        int pos;
        string curWord = *itr;
        pos = curWord.find(newGuess, reuseLetter+1);

        if (pos == string::npos) {
            partitions[0].insert(curWord);
        }
        else {
            for (int i = 0; i < word_l; i++) {
                if (pos == i) {
                    partitions[i+1].insert(curWord);
                }
            }
        }
    }

    for (map<int, set<string>>::iterator itr = partitions.begin(); itr != partitions.end(); itr++) {
        int size = (*itr).second.size();

        if (size > maxSize) {
            maxSize = size;
            maxIndex = (*itr).first;
        }
    }

    words = partitions[maxIndex];

    if (maxIndex != 0) {
        unkWord[maxIndex-1] = newGuess;
    }



    return;
}

int evilHangman(int guesses, int word_l, set<string>& words, char debug) {

    set<char> guessedChars;
    vector<char> unkWord(word_l, '_');

    while(guesses > 0) {
        curGameStatus(guesses, unkWord, words, debug);

        char newGuess = nextGuess(guessedChars);

        updateCurWords(newGuess, words, unkWord);

        if (count(unkWord.begin(), unkWord.end(), '_') == 0) {
            cout << "Well done, you've won!" << endl;
            cout << "The word was:" << endl;

            for (int i = 0; i < unkWord.size(); i++) {
                 cout << unkWord[i];
            }
            cout << endl;
            return 0;
        }
        guesses--;
    }

    guessedChars.clear();
    cout << "\n" << "You've lost" << endl;

    return 0;
}


int main() {

    int guesses;
    char debug, cont;
    bool valid, end = false;
    int word_l, min_l, max_l;
    set<string> dictionary, words;
    ifstream file ("di.txt");

    cout << "Welcome to Hangman." << endl;

    if (file.is_open()) {
        string temp;

        while (getline(file, temp)) {
            int cur_l = temp.length();
            dictionary.insert(temp);

            if (cur_l < min_l) {
                min_l = cur_l;
            }
            else if (cur_l > max_l) {
                max_l = cur_l;
            }
        }
        cout << "Dictionary created" << "\n" << endl;

    }
    else {
        cout << "Dictionary.txt could not be opened" << endl;
        return 1;
    }


    while (!end) {

        valid = false;
        while (!valid) {
            cout << "Please insert a valid word length: ";
            cin >> word_l;
            cout << endl;

            if (word_l >= min_l && word_l <= max_l) {
                valid = true;
            }
        }

        for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++) {
            string word = *it;

            if (word.length() == word_l) {
                words.insert(*it);
            }
        }


        valid = false;
        while (!valid) {
            cout << "Please insert a valid amount of guesses (more than 0): ";
            cin >> guesses;
            cout << endl;

            if (guesses > 0) {
                valid = true;
            }
        }

        valid = false;
        while (!valid) {
            cout << "Do you wanna activate testing mode? [y/n]: ";
            cin >> debug;
            cout << endl;

            if (debug == 'y' || debug == 'n') {
                valid = true;
            }
        }

        evilHangman(guesses, word_l, words, debug);

        cout << "Play again? [y/n]:";
        cin >> cont;
        cout << endl;

        while (true) {
            if (cont == 'n') {
                end = true;
                break;
            }
            else if (cont == 'y') {
                break;
            }
            else {
                cout << "y for yes and n for no, no?" << endl;
            }
        }
    }

    return 0;
}
