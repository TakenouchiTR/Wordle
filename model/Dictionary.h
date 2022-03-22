#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <unordered_set>
using namespace std;

namespace model
{

class Dictionary
{
    private:
        unordered_set<string> words;

    public:
        Dictionary(unordered_set<string>& words);
        virtual ~Dictionary();
        bool containsWord(const string& word) const;
        const string getRandomWord() const;
        const string getRandomWordWithUniqueLetters() const;

    protected:
};

}

#endif // DICTIONARY_H
