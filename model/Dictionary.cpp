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
    unsigned int wordCount = words.size();
    this->wordLookup = words;

    unordered_set<char> characters;
    for (const string& word : words)
    {
        allWords.push_back(word);

        characters.clear();

        bool hasDuplicates = false;
        for (unsigned int i = 0; i < word.size(); i++)
        {
            if (characters.find(word[i]) == characters.end())
            {
                characters.insert(word[i]);
            }
            else
            {
                hasDuplicates = true;
                break;
            }
        }
        if (!hasDuplicates)
        {
            this->wordsWithoutDuplicates.push_back(word);
        }
    }
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
    return this->wordLookup.find(word) != this->wordLookup.end();
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
    int index = rand() % this->allWords.size();
    return this->allWords[index];
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
    srand(time(0));
    int index = rand() % this->wordsWithoutDuplicates.size();
    return this->wordsWithoutDuplicates[index];
}

}
