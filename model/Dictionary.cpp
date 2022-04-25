#include "Dictionary.h"

#include <string>
#include <unordered_set>
#include <stdlib.h>
using namespace std;

namespace model
{

/**
    Creates an instance of dictionary with a set containing all words.

    precondition: None
    postcondition: All items in words is present in the dictionary.

    Params:
        words - The words that the dictionary will contain.
 */
Dictionary::Dictionary(unordered_set<string>& words)
{
    this->words = words;
}

Dictionary::~Dictionary()
{
    //dtor
}

/**
    Checks if the dictionary contains a word.

    precondition: None
    postcondition: None

    Params:
        word - The word to check.
    Return: Whether the word exists in the dictionary.
 */
bool Dictionary::containsWord(const string& word) const
{
    return this->words.find(word) != this->words.end();
}


/**
    Gets a random word from the dictionary.

    precondition: None
    postcondition: None

    Params: None
    Return: A random word contained in the dictionary.
 */
const string Dictionary::getRandomWord() const
{
    srand(time(0));
    int index = rand() % this->words.size();
    auto iter = this->words.begin();
    for (int i = 0; i < index; i++)
    {
        iter++;
    }
    return *iter;
}

/**
    Gets a random word from the dictionary without any repeating letters.

    precondition: None
    postcondition: None

    Params: None
    Return: A random word without repeating letters that is contained in the dictionary.
 */
const string Dictionary::getRandomWordWithUniqueLetters() const
{
    bool wordFound = false;
    string word;
    unordered_set<char> characters;

    while (!wordFound)
    {
        wordFound = true;
        characters.clear();
        word = this->getRandomWord();

        for (unsigned int i = 0; i < word.size(); i++)
        {
            if (characters.find(word[i]) == characters.end())
            {
                characters.insert(word[i]);
            }
            else
            {
                wordFound = false;
                break;
            }
        }
    }

    return word;
}

}
