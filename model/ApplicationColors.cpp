#include "ApplicationColors.h"

#include <FL/Fl.H>

#include <string>
#include <vector>
using namespace std;

namespace model
{
/**
    Creates an instance of ApplicationColors.

    Precondition: None
    Postcondition: None
 */
ApplicationColors::ApplicationColors()
{
    //ctor
}

ApplicationColors::~ApplicationColors()
{
    //dtor
}

/**
    Adds the specified color setting with title and values to the object.

    Precondition: None
    Postcondition: Colors have been added

    Param: title - name of the setting of colors
    Param: colors - the color values for this setting.
*/
void ApplicationColors::addColorSetting(const string& title, const vector<int>& colors)
{
    this->titles.push_back(title);
    this->colors.push_back(colors);
}

/**
    Gets the titles.

    Precondition: None
    Postcondition: None

    Returns: the titles.
*/
vector<string> ApplicationColors::getTitles() const
{
    return this->titles;
}

/**
    Gets the colors.

    Precondition: None
    Postcondition: None

    Returns: the colors.
*/
vector<vector<int>> ApplicationColors::getColors() const
{
    return this->colors;
}
}
