#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);
void transposeCheck(Dictionary& dict, set<string>& correctWords, const string& word);
void removeCheck(Dictionary& dict, set<string>& correctWords, const string& word);
void replaceCheck(Dictionary& dict, set<string>& correctWords, const string& word);
void insertCheck(Dictionary& dict, set<string>& correctWords, const string& word);


int main(int argc, char* argv[])
{
    // Output usage message if improper command line args were given.
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
        return EXIT_FAILURE;
    }

    ifstream inf(argv[2]);
    if (!inf)
    {
        cerr << "Could not open " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    // Read dictionary, but let user know what we are working on.
    cout << "Loading dictionary, this may take awhile...\n";

    Dictionary d(argv[1]);

    checkSpelling(inf, d);

    inf.close();

    return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict)
{
    int line_number = 0;

    while (in)
    {
        ++line_number;

        string line;
        getline(in, line);

        stringstream ss(stringstream::in | stringstream::out);
        ss << line;

        string word;
        // Set is used here to avoid duplicate suggestions
        // (default string comparator is used)
        set<string> correctWords;
        while (ss >> word)
        {
            word = stripPunct(word);
            lower(word);
            if (!dict.search(word))
            {
                // 1. Transposing of adjacent letters
                transposeCheck(dict, correctWords, word);
                // 2. Removal of each letter
                removeCheck(dict, correctWords, word);
                // 3. Replacement of each letter
                replaceCheck(dict, correctWords, word);
                // 4. Inserting any letter at any position in a word
                insertCheck(dict, correctWords, word);

                cout << "line " << line_number << ": '" << word << "'\n";
                cout << "\tsuggestions:\n";
                for (const string& cor : correctWords)
                    cout << "\t\t" << cor << "\n";
                correctWords.clear();
            }
        }
    }
}

void lower(string& s)
{
    // Ensures that a word is lowercase
    for (int i = 0; i < s.length(); ++i)
    {
        s[i] = tolower(s[i]);
    }
}

string stripPunct(const string& s)
{
    // Remove any single trailing
    // punctuation character from a word.
    if (ispunct(s[s.length() - 1]))
        return s.substr(0, s.length() - 1);

    return s;
}

void transposeCheck(Dictionary& dict, set<string>& correctWords, const string& word)
{
    for (int i = 0; i < word.length() - 1; ++i)
    {
        string temp(word);
        swap(temp[i], temp[i + 1]);
        if (dict.search(temp))
            correctWords.insert(temp);
    }
}

void removeCheck(Dictionary& dict, set<string>& correctWords, const string& word)
{
    for (int i = 0; i < word.length(); ++i)
    {
        string temp(word);
        temp.erase(i, 1);
        if (dict.search(temp))
            correctWords.insert(temp);
    }
}

void replaceCheck(Dictionary& dict, set<string>& correctWords, const string& word)
{
    for (int i = 0; i < word.length(); ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            string temp(word);
            temp[i] = c;
            if (dict.search(temp))
                correctWords.insert(temp);
        }
    }
}

void insertCheck(Dictionary& dict, set<string>& correctWords, const string& word)
{
    string temp(word);
    string::const_iterator iter = temp.begin();

    // Less or equal sign is accepted, because
    // strings in c++ have random access iterators,
    // and it is needed here to insert a letter
    // to the very end of the word
    while (iter <= temp.end())
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            iter = temp.insert(iter, c);
            if (dict.search(temp))
                correctWords.insert(temp);
            iter = temp.erase(iter);
        }
        ++iter;
    }
}