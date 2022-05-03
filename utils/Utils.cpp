#include "Utils.h"

#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

//
// Converts passed in string to an int
//
// @precondition none
// @postcondition none
// @throws Exception if text cannot be converted to an int
//
// @param text text to convert to an int
// @param errorMessage message thrown if a problem occurs when converting text to an int
//
// @return text converted to an int
//
int toInt(const string& text, const char* errorMessage)
{
    istringstream streamConversion(text);
    int value = 0;
    if (!(streamConversion >> value))
    {
        throw errorMessage;
    }

    return value;

}

//
// Converts and returns string in uppercase
//
// @precondition none
// @postcondition none
//
// @param text the text to convert to upper case
//
// @return Uppercase version of the string
//
const string toLowerCase(string text)
{
    transform(text.begin(), text.end(), text.begin(), ::tolower);

    return text;
}

//
// Checks is a file exists.
//
// @precondition none
// @postcondition none
//
// @param filePath The path to the file.
//
// @return true is the file exists, otherwise false.
//
bool fileExists(const string& filePath)
{
    ifstream checkFile(filePath);
    return checkFile.good();
}

/**
    Splits a string along a given character delimiter.

    Precondition: None
    Postcondition: None

    Params:
        text - The string to split.
        delimiter - The character to split on.
    Return: A vector containing all the sub strings from the split.
 */
vector<string> splitString(const string& text, const char delimiter)
{
    vector<string> result;
    int pos;
    int prevPos = 0;

    while ((pos = text.find(delimiter, prevPos)) != string::npos)
    {
        result.push_back(text.substr(prevPos, pos - prevPos));
        prevPos = pos + 1;
    }
    if (prevPos < text.size())
    {
        result.push_back(text.substr(prevPos, text.size() - prevPos));
    }


    return result;
}
