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

void WordleController::addLetterToGuess(char letter)
{
    this->guess += letter;
}

void WordleController::removeLetterFromGuess()
{
    if (this->guess.size() > 0)
    {
        this->guess.erase(this->guess.size() - 1);
    }
}

void WordleController::clearGuess()
{
    this->guess = "";
}

string& WordleController::getGuess()
{
    return this->guess;
}

bool WordleController::isGuessInDictionary()
{
    return this->dictionary->containsWord(this->guess);
}

bool WordleController::isUsingUniqueLetters()
{
    return this->useUniqueLetters;
}

void WordleController::setUsingUniqueLetters(bool useUniqueLetters)
{
    this->useUniqueLetters = useUniqueLetters;
}

}
