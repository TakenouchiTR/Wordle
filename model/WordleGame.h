#ifndef WORDLEGAME_H
#define WORDLEGAME_H

#define WORD_SIZE 5
#define MAX_GUESSES 6

#include <string>
using namespace std;

#include "Dictionary.h"
using namespace model;

#include "GuessStatus.h"

namespace model
{

class WordleGame
{
private:
    bool useUniqueLetters;
    string guess;
    string currentWord;
    Dictionary* dictionary;

public:
    WordleGame(Dictionary* dictionary);
    virtual ~WordleGame();
    void selectNewWord();
    GuessStatus* evaluateGuess();
    void addLetterToGuess(char letter);
    void removeLetterFromGuess();
    void clearGuess();
    const string& getGuess();
    const string& getCurrentWord();
    bool isGuessInDictionary();
    bool isUsingUniqueLetters();
    void setUsingUniqueLetters(bool useUniqueLetters);
};

}

#endif // WORDLEGAME_H
