#include "GameWindow.h"

#define MENU_HEIGHT 24
#define BOX_SIZE 30
#define PADDING 5

#include <FL/fl_ask.H>
#include <FL/Fl_Button.H>

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#include "DialogResult.h"
#include "WordleGame.h"
using namespace model;

#include "GameViewmodel.h"
using namespace viewmodel;

#include "AccountReader.h"
using namespace io;

#include "Utils.h"

namespace view
{
/**
    Creates an instance of GameWindow with width, height, and title.

    precondition: None
    postcondition: All values have been set.

    Params:
        width - The width of the application.
        height - The height of the application.
        title - The title of the application.
        controller - The controller for the application.
 */
GameWindow::GameWindow(int width, int height, const char* title, WordleGame* controller) : Fl_Window(width, height, title)
{
    this->viewmodel = new GameViewmodel(controller);
    this->callback(cbQuitPressed, this);

    begin();
    this->createLetterGrid();
    this->setupKeyboard();
    this->createMenuBar();
    this->answerBox = new Fl_Box(FL_NO_BOX, width / 2 - 40, 50, 80, 20, "");
    this->answerBox->align(FL_ALIGN_TOP);
    this->viewmodel->setAnswerBox(this->answerBox);
    end();
}

GameWindow::~GameWindow()
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

void GameWindow::createLetterGrid()
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

void GameWindow::setupKeyboard()
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

    this->viewmodel->setEnterButton(enterButton);
    this->viewmodel->setBackspaceButton(backButton);
}

void GameWindow::createKeyboardRow(int yCoord, const string& letters)
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

void GameWindow::createMenuBar()
{
    this->menuBar = new Fl_Menu_Bar(0, 0, this->w(), MENU_HEIGHT);
    this->menuBar->add("File/Quit", "", cbQuitPressed, this);
    this->menuBar->add("Game/Restart", "", cbRestartPressed, this);
    this->menuBar->add("Game/Switch Users", "", cbSwitchUsersPressed, this);
}

void GameWindow::show()
{
    Fl_Window::show();
    this->viewmodel->promptForAccount();
}

int GameWindow::handle(int event)
{
    Fl_Window::handle(event);
    switch(event)
    {
    case FL_KEYDOWN:
        return handleKeyDown(Fl::event_key());
    }
}

int GameWindow::handleKeyDown(int key)
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

void GameWindow::cbLetterButtonPressed(Fl_Widget* widget, void* data)
{
    Fl_Button* button = (Fl_Button*) widget;
    GameWindow* window = (GameWindow*) data;
    char letter = button->label()[0];
    window->viewmodel->addLetter(letter);
}

void GameWindow::cbEnterButtonPressed(Fl_Widget* widget, void* data)
{
    ((GameWindow*)data)->viewmodel->makeGuess();
}

void GameWindow::cbBackspaceButtonPressed(Fl_Widget* widget, void* data)
{
    ((GameWindow*)data)->viewmodel->removeLetter();
}

void GameWindow::cbRestartPressed(Fl_Widget* widget, void* data)
{
    ((GameWindow*)data)->viewmodel->restartGame();
}

void GameWindow::cbSwitchUsersPressed(Fl_Widget* widget, void* data)
{
    ((GameWindow*)data)->viewmodel->switchUsers();
}

void GameWindow::cbQuitPressed(Fl_Widget* widget, void* data)
{
    if (((GameWindow*)data)->viewmodel->quitGame())
    {
        ((GameWindow*)data)->hide();
    }
}

}
