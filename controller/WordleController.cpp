#include "WordleController.h"

#define DEBUG_OUTPUT

#include <stdexcept>
#include <unordered_map>
#include <iostream>
using namespace std;

#include "Dictionary.h"
using namespace model;

#include "GuessStatus.h"

namespace controller
{

/**
    Creates an instance of WordController with a specified dictionary.

    Precondition: None
    Postcondition: this->getGuess() == "" &&
                   this->isUsingUniqueLetters() &&
                   Only words present in the dictionary are valid guesses

    Params:
        dictionary - The dictionary containing all valid words
 */
WordleController::WordleController(Dictionary* dictionary)
{
    this->guess = "";
    this->currentWord = "";
    this->useUniqueLetters = true;
    this->dictionary = dictionary;
}

WordleController::~WordleController()
{
    //dtor
}

/**
    Randomly selects a word from the controller's dictionary. If this->isUsingUniqueLetters(), then
    the word will not have any duplicate letters in it.

    Precondition: None
    Postcondition: The controller will have a new word from the dictionary to guess

    Params: None
    Return: None
 */
void WordleController::selectNewWord()
{
    if (this->useUniqueLetters)
    {
        this->currentWord = this->dictionary->getRandomWordWithUniqueLetters();
    }
    else
    {
        this->currentWord = this->dictionary->getRandomWord();
    }
#ifdef DEBUG_OUTPUT
    cout << this->currentWord << endl;
#endif // DEBUG_OUTPUT
}

/**
    Evaluates this->getGuess() against the current word.

    Precondition: None
    Postcondition: None

    Params: None
    Return: An array of size this->getGuess().size() containing the status of each
                letter.
 */
GuessStatus* WordleController::evaluateGuess()
{
    if (guess.size() != this->currentWord.size())
    {
        throw runtime_error("Guess is size does not match word size");
    }

    GuessStatus *result = new GuessStatus[guess.size()];
    unordered_map<char, int> cache;

    for (unsigned int i = 0; i < guess.size(); i++)
    {
        char letter = this->currentWord[i];
        result[i] = GuessStatus::DOES_NOT_EXIST;

        if (cache.find(letter) == cache.end())
        {
            cache[letter]++;
        }
        else
        {
            cache[letter] = 1;
        }
    }

    for (unsigned int i = 0; i < guess.size(); i++)
    {
        char letter = guess[i];
        if (letter == this->currentWord[i])
        {
            result[i] = GuessStatus::CORRECT_POSITION;
            if (cache[letter] == 1)
            {
                cache.erase(letter);
            }
            else
            {
                cache[letter]--;
            }
        }
    }
    for (unsigned int i = 0; i < guess.size(); i++)
    {
        if (result[i] == GuessStatus::CORRECT_POSITION)
        {
            continue;
        }

        char letter = guess[i];
        if (cache.find(letter) != cache.end() && cache[letter] > 0)
        {
            result[i] = GuessStatus::INCORRECT_POSITION;
            cache[letter]--;
        }
    }

    return result;
}

/**
    Adds a letter to the end of this->getGuess().

    Precondition: None
    Postcondition: this->getGuess() == this->getGuess()@prev + letter

    Params: None
    Return: None
 */
void WordleController::addLetterToGuess(char letter)
{
    this->guess += letter;
}

/**
    Removes a letter from the end of this->getGuess(). If this->getGuess() is empty,
    no action will occur.

    Precondition: None
    Postcondition: if this->getGuess().size()@prev > 0,
                       this->getGuess() == this->getGuess().substr(0, this->getGuess().size() - 2)@prev
                   otherwise None.

    Params: None
    Return: None
 */
void WordleController::removeLetterFromGuess()
{
    if (this->guess.size() > 0)
    {
        this->guess.erase(this->guess.size() - 1);
    }
}

/**
    Clears the current guess.

    Precondition: None
    Postcondition: this->getGuess() == ""

    Params: None
    Return: None
 */
void WordleController::clearGuess()
{
    this->guess = "";
}

/**
    Gets the current guess.

    Precondition: None
    Postcondition: None

    Params: None
    Return: The current guess.
 */
const string& WordleController::getGuess()
{
    return this->guess;
}

/**
    Gets the current word.

    Precondition: None
    Postcondition: None

    Params: None
    Return: The current word.
 */
const string& WordleController::getCurrentWord()
{
    return this->currentWord;
}

/**
    Checks whether the current guess is in the dictionary.

    Precondition: None
    Postcondition: None

    Params: None
    Return: Whether the current guess is in the dictionary.
 */
bool WordleController::isGuessInDictionary()
{
    return this->dictionary->containsWord(this->guess);
}

/**
    Gets whether or not words with duplicated letters can be randomly selected when
    pucking a new word to guess.

    Precondition: None
    Postcondition: None

    Params: None
    Return: Whether words with duplicated letters can be chosen.
 */
bool WordleController::isUsingUniqueLetters()
{
    return this->useUniqueLetters;
}

/**
    Sets whether or not words with duplicated letters can be randomly selected when
    pucking a new word to guess.

    Precondition: None
    Postcondition: this->isUsingUniqieLetters() == useUniqueLetters

    Params: None
    Return: None
 */
void WordleController::setUsingUniqueLetters(bool useUniqueLetters)
{
    this->useUniqueLetters = useUniqueLetters;
}

}
