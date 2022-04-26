#ifndef WORDLEMAINWINDOW_H
#define WORDLEMAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

#include <string>
using namespace std;

#include "WordleController.h"
using namespace controller;

namespace view
{
class WordleMainWindow : public Fl_Window
{
public:
    WordleMainWindow(int width, int height, const char* title, WordleController* cotroller);
    virtual ~WordleMainWindow();

private:
    static const int NUMBER_OF_ROWS = 6;
    static const int NUMBER_OF_COLUMNS = 5;
    int currentRow;
    int currentColumn;
    char currentWord[NUMBER_OF_COLUMNS];
    Fl_Box* winMessage;
    Fl_Box* boxes[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
    WordleController* controller;
    int handle(int event);
    int handleKeyDown(int key);
    int handleBackspace();
    int handleLetterKeyPress(int key);
    int handleEnter();
    Fl_Box* getCurrentBox();
    void setWinState();
    void updateGUI();
};
}


#endif // WORDLEMAINWINDOW_H
