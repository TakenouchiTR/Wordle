#ifndef UTILS_H
#define UTILS_H

#include <string>
using namespace std;

int toInt(const string& text, const char* errorMessage);
const string toLowerCase(string text);
bool fileExists(const string& filePath);

#endif // UTILS_H
