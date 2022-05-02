#include "WordleMainWindow.h"

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

    begin();
    this->createLetterGrid();
    this->setupKeyboard();
    this->winMessage = new Fl_Box(FL_NO_BOX, 250, 50, 200, 50, "");
    end();
}

WordleMainWindow::~WordleMainWindow()
{
    for (int i = 0; i < GUESS_COUNT; ++i)
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
}

void WordleMainWindow::createLetterGrid()
{
    int boxYPosition = 20;
    int boxSquareSize = 30;
    int xIncrement = boxSquareSize + 5;
    int yIncrement = boxSquareSize + 10;

    for (int i = 0; i < GUESS_COUNT; ++i)
    {
        int boxXPosition = 50;
        for (int j = 0; j < WORD_SIZE; ++j)
        {
            Fl_Box* box = new Fl_Box(boxXPosition, boxYPosition, boxSquareSize, boxSquareSize, "");
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
    this->createKeyboardRow(50, 300, 5, 30, "qwertyuiop");
    this->createKeyboardRow(67, 340, 5, 30, "asdfghjkl");
    this->createKeyboardRow(102, 380, 5, 30, "zxcvbnm");

    Fl_Button* enterButton = new Fl_Button(50, 380, 45, 30, "Enter");
    Fl_Button* backButton = new Fl_Button(347.5, 380, 45, 30, "Back");

    enterButton->callback(cbEnterButtonPressed, this);
    backButton->callback(cbBackspaceButtonPressed, this);
}

void WordleMainWindow::createKeyboardRow(int startX, int yCoord, int padding, int buttonSize, const string& letters)
{
    int xOffset = buttonSize + padding;
    for (unsigned int i = 0; i < letters.size(); i++)
    {
        char letter[1];
        letter[0] = letters[i];

        Fl_Button* button = new Fl_Button(startX + xOffset * i, yCoord, buttonSize, buttonSize, "");
        this->letterButtons[letters[i]] = button;
        this->viewmodel->setLetterButton(letters[i], button);

        button->copy_label(letter);
        button->callback(cbLetterButtonPressed, this);
    }
}

void WordleMainWindow::show()
{
    Fl_Window::show();
    this->viewmodel->promptForAccount();
    cout << "End of WordleMainWIndow show" << endl;
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
}
