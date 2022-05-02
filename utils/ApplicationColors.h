#ifndef APPLICATIONCOLORS_H
#define APPLICATIONCOLORS_H

#include <string>
#include <vector>
using namespace std;

/**
Data pertaining to the colors of the application.

Author: Alexander Ayers
Version: Spring 2022
*/
namespace utils
{
class ApplicationColors
{
public:
    ApplicationColors();
    virtual ~ApplicationColors();
    void addColorSetting(const string& title, const vector<int>& colors);
    vector<string> getTitles() const;
    vector<vector<int>> getColors() const;

private:
    vector<string> titles;
    vector<vector<int>> colors;

};
}

#endif // APPLICATIONCOLORS_H
