#ifndef APPLICATIONCOLORS_H
#define APPLICATIONCOLORS_H
#define NUMBER_OF_COLOR_BLINDNESS_OPTIONS 4
#define NUMBER_OF_APPLICATION_COLORS 4

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
    static const string& COLOR_BLINDNESS_TEXT[NUMBER_OF_COLOR_BLINDNESS_OPTIONS] = {"Normal Vision", "Deuteranopia", "Protanopia", "Tritanopia"};
    static const int[NUMBER_OF_COLOR_BLINDNESS_OPTIONS][NUMBER_OF_APPLICATION_COLORS] STATUS_COLORS = {NORMAL_VISION_COLORS, DEUTERANOPIA_COLORS, PROTANOPIA_COLORS, TRITANOPIA_COLORS}

private:
    static const int NORMAL_VISION_COLORS[NUMBER_OF_APPLICATION_COLORS] = {49, 45, 95, 63}
    static const int DEUTERANOPIA_COLORS[NUMBER_OF_APPLICATION_COLORS] = {49, 45, 124, 175}
    static const int PROTANOPIA_COLORS[NUMBER_OF_APPLICATION_COLORS] = {49, 45, 84, 95}
    static const int TRITANOPIA_COLORS[NUMBER_OF_APPLICATION_COLORS] = {49, 45, 253, 191}



};
}

#endif // APPLICATIONCOLORS_H
