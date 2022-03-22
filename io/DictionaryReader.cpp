#include "DictionaryReader.h"

#include <stdexcept>
#include <unordered_set>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "Dictionary.h"
using namespace model;

#include "Utils.h"

namespace io
{

DictionaryReader::DictionaryReader()
{
    //ctor
}

DictionaryReader::~DictionaryReader()
{
    //dtor
}

/**
    Reads a file and retrieves a set containing all of the words of a specified length.
    Each line in the file must contain a single word.

    @precondition wordLength > 0 && Utils::fileExists(filePath)
    @postCondition None

    Params:
        wordLength - The specified length of the word.
        filePath - The path to the dictionary file
    Return: A Dictionary all words with the specified length stored in the file.
    Throws:
        runtime_error - File not found
 */
Dictionary DictionaryReader::readFile(int wordLength, const string& filePath)
{
    if (!fileExists(filePath))
    {
        throw runtime_error("File " + filePath + " not found.");
    }

    unordered_set<string> words;
    ifstream fileStream(filePath);
    string line;

    while (fileStream >> line)
    {
        if (line.size() == wordLength)
        {
            words.insert(line);
        }
    }

    return Dictionary(words);
}

}
