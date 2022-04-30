#ifndef WORDLEMAINWINDOW_H
#define WORDLEMAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

#include <string>
#include <unordered_map>
using namespace std;

#include "WordleController.h"
#include "GuessStatus.h"
using namespace controller;

#include "AccountManager.h"
using namespace model;

namespace view
{
class WordleMainWindow : public Fl_Window
{
private:
    static const int NUMBER_OF_ROWS = 6;
    static const int NUMBER_OF_COLUMNS = 5;
    static const int STATUS_COLORS[];

    int currentRow;
    int currentColumn;
    unordered_map<char, Fl_Button*> letterButtons;
    unordered_map<char, GuessStatus> letterStatuses;
    Fl_Box* winMessage;
    Fl_Box* boxes[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
    Fl_Button* testButton;
    WordleController* controller;
    AccountManager accountManager;
    UserAccount currentUser;

    void setupKeyboard();
    void createKeyboardRow(int startX, int yCoord, int padding, int buttonSize, const string& letters);

    void promptForAccount();
    int handle(int event);
    int handleKeyDown(int key);
    int handleBackspace();
    int handleLetterKeyPress(char key);
    int handleEnter();
    Fl_Box* getCurrentBox();
    void setWinState();
    void updateGUI();

    static void cbLetterButtonPressed(Fl_Widget* widget, void* data);
    static void cbEnterButtonPressed(Fl_Widget* widget, void* data);
    static void cbBackspaceButtonPressed(Fl_Widget* widget, void* data);

public:
    WordleMainWindow(int width, int height, const char* title, WordleController* cotroller);
    virtual ~WordleMainWindow();
    void show();
};
}


#endif // WORDLEMAINWINDOW_H
