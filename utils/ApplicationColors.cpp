#include "ApplicationColors.h"

#include <FL/Fl.H>

namespace utils
{
    /**
    Text Versions of Each Color Blindness Option.
    */
   const string ApplicationColors::COLOR_BLINDNESS_TEXT[NUMBER_OF_COLOR_BLINDNESS_OPTIONS] = {"Normal Vision", "Deuteranopia", "Protanopia", "Tritanopia"};
    /**
    Two-Dimensional Array containing each set of colors for the statuses for each color-blindness setting.
    */
   const int ApplicationColors::STATUS_COLORS[NUMBER_OF_COLOR_BLINDNESS_OPTIONS][NUMBER_OF_APPLICATION_COLORS] = {{FL_GRAY, FL_DARK2, FL_YELLOW, FL_GREEN}, {FL_GRAY, FL_DARK2, 124, 175}, {FL_GRAY, FL_DARK2, 84, FL_YELLOW}, {FL_GRAY, FL_DARK2, 253, 191}};
}
