#ifndef WORDLECONTROLLER_H
#define WORDLECONTROLLER_H

#include <string>
using namespace std;

#include "Dictionary.h"
using namespace model;

#include "GuessStatus.h"

namespace controller
{

class WordleController
{
private:
    bool useUniqueLetters;
    string currentWord;
    Dictionary* dictionary;

public:
    WordleController(Dictionary* dictionary);
    virtual ~WordleController();
    void selectNewWord();
    GuessStatus* evaluateGuess(const string& guess);
    bool isUsingUniqueLetters();
    void setUsingUniqueLetters(bool useUniqueLetters);
};

}

#endif // WORDLECONTROLLER_H
