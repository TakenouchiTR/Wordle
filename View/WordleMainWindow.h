#ifndef WORDLEMAINWINDOW_H
#define WORDLEMAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

#include <string>
using namespace std;

namespace view
{
class WordleMainWindow : public Fl_Window
{
public:
    WordleMainWindow(int width, int height, const char* title);
    virtual ~WordleMainWindow();
    int handle(int event);


private:
    static const int NUMBER_OF_ROWS = 6;
    static const int NUMBER_OF_COLUMNS = 5;
    int currentRow;
    int currentColumn;
    string currentWord;
    Fl_Box* boxes[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
    int handleKeyDown(int event, int key);
    Fl_Box* getCurrentBox();

};
}


#endif // WORDLEMAINWINDOW_H
