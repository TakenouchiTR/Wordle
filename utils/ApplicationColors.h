#ifndef APPLICATIONCOLORS_H
#define APPLICATIONCOLORS_H
#define NUMBER_OF_COLOR_BLINDNESS_OPTIONS 4
#define NUMBER_OF_APPLICATION_COLORS 4

#include <string>
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
    /**
    Controlled-Value for Color-Blindness
    */
    enum ColorBlindnessOption
    {
        /**
        Default Values for Colors
        */
        NORMAL_VISION,
        /**
        Color-Blindness that Can't see Red.
        */
        DEUTERANOPIA,
        /**
        Color-Blindness that Can't see Green.
        */
        PROTANOPIA,
        /**
        Color-Blindness that Can't see Blue.
        */
        TRITANOPIA
    };
    static const string COLOR_BLINDNESS_TEXT[];
    /**
    Two-Dimensional Array containing each set of colors for the statuses for each color-blindness setting.
    */
    static const int STATUS_COLORS[NUMBER_OF_COLOR_BLINDNESS_OPTIONS][NUMBER_OF_APPLICATION_COLORS];


};
}

#endif // APPLICATIONCOLORS_H
