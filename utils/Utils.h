#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
using namespace std;

int toInt(const string& text, const char* errorMessage);
const string toLowerCase(string text);
bool fileExists(const string& filePath);
vector<string> splitString(const string& text, const char delimiter);

#endif // UTILS_H
