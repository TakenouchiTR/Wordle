#include "Utils.h"

#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

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
