#include "WordleMainWindow.h"
using namespace view;

int main (int argc, char ** argv)
{
    WordleMainWindow window(500, 500, "Team C's Wordle Application");
    window.show();

    int exitCode = Fl::run();
    return exitCode;
}
