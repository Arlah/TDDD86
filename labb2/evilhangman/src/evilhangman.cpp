#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


void curGameStatus(const int& guesses, const vector<char>& unkWord, const set<string>& words, const char& debug) {

    for (unsigned int i = 0; i < unkWord.size(); i++) {
        cout << " " << unkWord[i] << " ";
    }
    cout << "\n" << endl;

    cout << "You have " << guesses << " guesses left" << endl;

    if (debug == 'y') {
        cout << "Words left: " << words.size()  << endl;
    }

    return;
}

void nextGuess(char& newGuess, set<char>& guessedChars) {

    cout << "Enter your guess: ";
    char newChar;
    string newString;

    while (true) {
        cin >> newString;
        if (newString.length() == 1 && ALPHABET.find(newString) != string::npos) {
            newChar = newString[0];

            if (guessedChars.find(newChar) == guessedChars.end()) {
                guessedChars.insert(newChar);
                break;
            }
            else {
                cout << "Already tried letter, choose a new one: ";
            }
        }
        else {
            cout << "Enter one lowercase english character" << endl;
        }
    }

    cout << endl;
    newGuess = newChar;
}

void newWordFamilies(const char& newGuess, set<string>& words, map<string, set<string>>& wordFamilies) {
    //map<string, set<string> > wordFamilies;

    for(set<string>::iterator wordPtr = words.begin(); wordPtr != words.end(); wordPtr++) {

        string familyType = "";

        for (unsigned int i = 0; i < wordPtr->size(); i++) {

            if (wordPtr->at(i) == newGuess) {
                familyType += newGuess;
            } else {
                familyType += '_';
            }
        }

        if (wordFamilies.count(familyType)) {
            // operator[] returns a reference to the map element. Important for efficiency
            wordFamilies[familyType].insert(*wordPtr);
        }
        else {
            set<string> familySet;
            familySet.insert(*wordPtr);
            wordFamilies[familyType] = familySet;
        }
    }
}

void CountLargestFamily(map<string, set<string> >& wordFamilies, set<string>& words) {
    words.clear();

    for (map<string, set<string>>::iterator pairItr = wordFamilies.begin(); pairItr != wordFamilies.end(); pairItr++) {
        set<string> wordFamily = pairItr->second;

        if (wordFamily.size() > words.size()) {
            words = wordFamily;
        }
    }
}

void updateCurWords(const char& newGuess, set<string>& words) {

    map<string, set<string>> wordFamilies;
    newWordFamilies(newGuess, words, wordFamilies);

    CountLargestFamily(wordFamilies, words);
}

void updateGuesses(const char& newGuess, int& guesses, set<string>& words) {

    set<string>::iterator wordPtr = words.begin();

    if (wordPtr -> find(newGuess) == -1) {
        cout << "Incorrect guess." << endl;
        guesses--;
    }
    else {
        cout << "Correct guess" << endl;
    }
}

void updateUnkWord(const char& newGuess, const set<string> words, vector<char>& unkWord) {

    set<string>::iterator ptr = words.begin();

    for (unsigned int i = 0; i < ptr -> size(); i++) {
        if (ptr -> at(i) == newGuess) {
            unkWord[i] = newGuess;
        }
    }
}

int evilHangman(int& guesses, int word_l, set<string>& words, const char& debug) {

    char newGuess;
    set<char> guessedChars;
    vector<char> unkWord(word_l, '_');

    while(guesses > 0) {
        curGameStatus(guesses, unkWord, words, debug);

        nextGuess(newGuess, guessedChars);

        updateCurWords(newGuess, words);

        updateGuesses(newGuess, guesses, words);

        updateUnkWord(newGuess, words, unkWord);

        if (count(unkWord.begin(), unkWord.end(), '_') == 0) {
            cout << "Well done, you've won!" << endl;
            cout << "The word was:" << "\n" << endl;

            for (unsigned int i = 0; i < unkWord.size(); i++) {
                 cout << unkWord[i];
            }
            cout << "\n" << endl;
            return 0;
        }
        //guesses--;
    }

    guessedChars.clear();
    cout << "\n" << "You've lost" << endl;

    return 0;
}


int main() {

    int guesses;
    char debug, cont;
    bool valid, end = false;
    set<string> dictionary, words;
    unsigned int word_l, min_l, max_l;
    ifstream file ("dictionary.txt");

    cout << "Welcome to Hangman." << endl;

    if (file.is_open()) {
        string temp;

        while (getline(file, temp)) {
            unsigned int cur_l = temp.length();
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

        while (true) {
            cout << "Play again? [y/n]:";
            cin >> cont;
            cout << endl;

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
