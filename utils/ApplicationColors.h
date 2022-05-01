#ifndef APPLICATIONCOLORS_H
#define APPLICATIONCOLORS_H

/**
Data pertaining to the colors of the application.

Author: Alexander Ayers
Version: Spring 2022
*/
namespace view
{
class ApplicationColors
{
public:
    /**
    Controlled-Value
    */
    enum ColorBlindnessOptions
    {
        NORMAL_VISION,
        DEUTERANOPIA,
        PROTANOPIA,
        TRITANOPIA
    };
    const string& ColorBlindessText[COLOR_BLINDNESS_COUNT] = {"Normal Vision", "Deuteranopia", "Protanopia", "Tritanopia"};


};
}

#endif // APPLICATIONCOLORS_H
