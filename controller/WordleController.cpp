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

GuessStatus* WordleController::evaluateGuess(const string& guess)
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

}
