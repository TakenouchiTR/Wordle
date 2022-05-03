#ifndef WORDLEMAINWINDOW_H
#define WORDLEMAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>

#include <string>
#include <unordered_map>
using namespace std;

#include "WordleController.h"
#include "GuessStatus.h"
using namespace controller;

#include "GameViewmodel.h"
using namespace viewmodel;

#include "AccountManager.h"
using namespace model;

namespace view
{
class WordleMainWindow : public Fl_Window
{
private:
    Fl_Menu_Bar* menuBar;
    Fl_Box* winMessage;
    Fl_Box* boxes[MAX_GUESSES][WORD_SIZE];
    Fl_Button* enterButton;
    Fl_Button* backButton;
    unordered_map<char, Fl_Button*> letterButtons;

    GameViewmodel* viewmodel;

    void createLetterGrid();
    void setupKeyboard();
    void createKeyboardRow(int yCoord, const string& letters);
    void createMenuBar();

    int handle(int event);
    int handleKeyDown(int key);
    Fl_Box* getCurrentBox();

    static void cbLetterButtonPressed(Fl_Widget* widget, void* data);
    static void cbEnterButtonPressed(Fl_Widget* widget, void* data);
    static void cbBackspaceButtonPressed(Fl_Widget* widget, void* data);
    static void cbRestartPressed(Fl_Widget* widget, void* data);
    static void cbSwitchUsersPressed(Fl_Widget* widget, void* data);
    static void cbQuitPressed(Fl_Widget* widget, void* data);

public:
    WordleMainWindow(int width, int height, const char* title, WordleController* cotroller);
    virtual ~WordleMainWindow();
    void show();
};
}


#endif // WORDLEMAINWINDOW_H
