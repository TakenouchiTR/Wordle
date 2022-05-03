#include "WordleMainWindow.h"

#define MENU_HEIGHT 24
#define BOX_SIZE 30
#define PADDING 5

#include <FL/fl_ask.H>
#include <FL/Fl_Button.H>

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#include "WordleController.h"
using namespace controller;

#include "GameViewmodel.h"
using namespace viewmodel;

#include "AccountSelectWindow.h"
#include "DialogResult.h"

#include "AccountReader.h"
using namespace io;

#include "Utils.h"

namespace view
{
/**
    Creates an instance of WordleMainWindow with width, height, and title.

    precondition: None
    postcondition: All values have been set.

    Params:
        width - The width of the application.
        height - The height of the application.
        title - The title of the application.
        controller - The controller for the application.
 */
WordleMainWindow::WordleMainWindow(int width, int height, const char* title, WordleController* controller) : Fl_Window(width, height, title)
{
    this->viewmodel = new GameViewmodel(controller);
    this->callback(cbQuitPressed, this);

    begin();
    this->createLetterGrid();
    this->setupKeyboard();
    this->createMenuBar();
    this->winMessage = new Fl_Box(FL_NO_BOX, 250, 50, 200, 50, "");
    end();
}

WordleMainWindow::~WordleMainWindow()
{
    for (int i = 0; i < MAX_GUESSES; ++i)
    {
        for (int j = 0; j < WORD_SIZE; ++j)
        {
            delete this->boxes[i][j];
        }
    }
    for (char letter = 'a'; letter <= 'z'; letter++)
    {
        delete(this->letterButtons[letter]);
    }
    delete this->viewmodel;
    delete this->menuBar;
    delete this->enterButton;
    delete this->backButton;
}

void WordleMainWindow::createLetterGrid()
{
    int boxYPosition = MENU_HEIGHT + 40;
    int xIncrement = BOX_SIZE + PADDING;
    int yIncrement = BOX_SIZE + PADDING;
    int rowWidth = xIncrement * WORD_SIZE - PADDING;
    int startX = (this->w() - rowWidth) / 2;

    for (int i = 0; i < MAX_GUESSES; ++i)
    {
        int boxXPosition = startX;
        for (int j = 0; j < WORD_SIZE; ++j)
        {
            Fl_Box* box = new Fl_Box(boxXPosition, boxYPosition, BOX_SIZE, BOX_SIZE, "");
            box->box (FL_UP_BOX);
            this->boxes[i][j] = box;
            this->viewmodel->setBox(i, j, box);
            boxXPosition += xIncrement;
        }
        boxYPosition += yIncrement;
    }
}

void WordleMainWindow::setupKeyboard()
{
    const int LONGEST_ROW = 10;
    const int KEYBOARD_WIDTH = (BOX_SIZE + PADDING) * LONGEST_ROW - PADDING;
    const int START_Y = 290;

    this->createKeyboardRow(START_Y, "qwertyuiop");
    this->createKeyboardRow(START_Y + BOX_SIZE + PADDING, "asdfghjkl");
    this->createKeyboardRow(START_Y + (BOX_SIZE + PADDING) * 2, "zxcvbnm");

    int enterXPos = (this->w() - KEYBOARD_WIDTH) / 2;
    int backXPos = (this->w() + KEYBOARD_WIDTH) / 2 - BOX_SIZE * 1.5;
    this->enterButton = new Fl_Button(enterXPos, START_Y + (BOX_SIZE + PADDING) * 2, BOX_SIZE * 1.5, BOX_SIZE, "Enter");
    this->backButton = new Fl_Button(backXPos, START_Y + (BOX_SIZE + PADDING) * 2, BOX_SIZE * 1.5, BOX_SIZE, "Back");

    enterButton->callback(cbEnterButtonPressed, this);
    backButton->callback(cbBackspaceButtonPressed, this);
}

void WordleMainWindow::createKeyboardRow(int yCoord, const string& letters)
{
    int xIncrement = BOX_SIZE + PADDING;
    int rowWidth = xIncrement * letters.size() - PADDING;
    int startX = (this->w() - rowWidth) / 2;

    for (unsigned int i = 0; i < letters.size(); i++)
    {
        char letter[1];
        letter[0] = letters[i];

        Fl_Button* button = new Fl_Button(startX + xIncrement * i, yCoord, BOX_SIZE, BOX_SIZE, "");
        this->letterButtons[letters[i]] = button;
        this->viewmodel->setLetterButton(letters[i], button);

        button->copy_label(letter);
        button->callback(cbLetterButtonPressed, this);
    }
}

void WordleMainWindow::createMenuBar()
{
    this->menuBar = new Fl_Menu_Bar(0, 0, this->w(), MENU_HEIGHT);
    this->menuBar->add("File/Quit", "", cbQuitPressed, this);
    this->menuBar->add("Game/Restart", "", cbRestartPressed, this);
    this->menuBar->add("Game/Switch Users", "", cbSwitchUsersPressed, this);
}

void WordleMainWindow::show()
{
    Fl_Window::show();
    this->viewmodel->promptForAccount();
}

int WordleMainWindow::handle(int event)
{
    Fl_Window::handle(event);
    switch(event)
    {
    case FL_KEYDOWN:
        return handleKeyDown(Fl::event_key());
    }
}

int WordleMainWindow::handleKeyDown(int key)
{
    if (key == FL_Enter)
    {
        this->viewmodel->makeGuess();
    }
    if (key == FL_BackSpace)
    {
        this->viewmodel->removeLetter();
    }
    if (key >= 'a' && key <= 'z')
    {
        this->viewmodel->addLetter((char) key);
    }
}

void WordleMainWindow::cbLetterButtonPressed(Fl_Widget* widget, void* data)
{
    Fl_Button* button = (Fl_Button*) widget;
    WordleMainWindow* window = (WordleMainWindow*) data;
    char letter = button->label()[0];
    window->viewmodel->addLetter(letter);
}

void WordleMainWindow::cbEnterButtonPressed(Fl_Widget* widget, void* data)
{
    ((WordleMainWindow*)data)->viewmodel->makeGuess();
}

void WordleMainWindow::cbBackspaceButtonPressed(Fl_Widget* widget, void* data)
{
    ((WordleMainWindow*)data)->viewmodel->removeLetter();
}

void WordleMainWindow::cbRestartPressed(Fl_Widget* widget, void* data)
{
    ((WordleMainWindow*)data)->viewmodel->restartGame();
}

void WordleMainWindow::cbSwitchUsersPressed(Fl_Widget* widget, void* data)
{
    ((WordleMainWindow*)data)->viewmodel->switchUsers();
}

void WordleMainWindow::cbQuitPressed(Fl_Widget* widget, void* data)
{
    if (((WordleMainWindow*)data)->viewmodel->quitGame())
    {
        ((WordleMainWindow*)data)->hide();
    }
}

}
