#include "WordleMainWindow.h"

#define WORD_SIZE 5
#define FILE_PATH "data.csv"

#include <FL/fl_ask.H>
#include <FL/Fl_Button.H>

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#include "WordleController.h"
#include "GuessStatus.h"
using namespace controller;

#include "AccountSelectWindow.h"
#include "DialogResult.h"

#include "AccountReader.h"
using namespace io;

#include "Utils.h"

namespace view
{
const int WordleMainWindow::STATUS_COLORS[4] = {49, 45, 95, 63};

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
    this->currentRow = 0;
    this->currentColumn = 0;
    this->controller = controller;

    if (fileExists(FILE_PATH))
    {
        try
        {
            AccountReader reader;
            this->accountManager = reader.readFile(FILE_PATH);
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }

    begin();
    int boxYPosition = 20;
    int boxSquareSize = 30;
    int xIncrement = boxSquareSize + 5;
    int yIncrement = boxSquareSize + 10;

    for (int i = 0; i < WordleMainWindow::NUMBER_OF_ROWS; ++i)
    {
        int boxXPosition = 50;
        for (int j = 0; j < WordleMainWindow::NUMBER_OF_COLUMNS; ++j)
        {
            Fl_Box* box = new Fl_Box(boxXPosition, boxYPosition, boxSquareSize, boxSquareSize, "");
            box->box (FL_UP_BOX);
            this->boxes[i][j] = box;
            boxXPosition += xIncrement;
        }
        boxYPosition += yIncrement;
    }

    this->setupKeyboard();

    this->winMessage = new Fl_Box(FL_NO_BOX, 250, 50, 200, 50, "");
    end();
}

WordleMainWindow::~WordleMainWindow()
{
    for (int i = 0; i < WordleMainWindow::NUMBER_OF_ROWS; ++i)
    {
        for (int j = 0; j < WordleMainWindow::NUMBER_OF_COLUMNS; ++j)
        {
            delete this->boxes[i][j];
        }
    }
    delete this->controller;
    delete this->winMessage;
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
        char letter1 = letters[i];
        char letter[1];
        letter[0] = letters[i];

        Fl_Button* button = new Fl_Button(startX + xOffset * i, yCoord, buttonSize, buttonSize, "");
        this->letterButtons[letters[i]] = button;
        this->letterStatuses[letters[i]] = GuessStatus::UNKNOWN;

        button->copy_label(letter);
        button->callback(cbLetterButtonPressed, this);
    }
}

void WordleMainWindow::show()
{
    Fl_Window::show();
    this->promptForAccount();
}

void WordleMainWindow::promptForAccount()
{
    AccountSelectWindow window(this->accountManager);
    window.set_modal();
    while (window.getResult() == DialogResult::CANCELLED)
    {
        window.show();
        while(window.shown())
        {
            Fl::wait();
        }
    }
    this->currentUser = window.getAccount();
    this->controller->setUsingUniqueLetters(this->currentUser.isUsingUniqueLetters());
    this->controller->selectNewWord();
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
        handleEnter();
    }
    if (key == FL_BackSpace)
    {
        handleBackspace();
    }
    if (key >= 'a' && key <= 'z')
    {
        handleLetterKeyPress((char) key);
    }
}

int WordleMainWindow::handleEnter()
{
    if (!this->controller->isGuessInDictionary())
    {
        if (this->controller->getGuess().size() == WORD_SIZE)
        {
            fl_alert("\"%s\" is not a known word.", this->controller->getGuess().c_str());
        }
        return 0;
    }

    GuessStatus* verification = this->controller->evaluateGuess();
    string guess = this->controller->getGuess();
    int correctLetters = 0;

    for (int i = 0; i < WordleMainWindow::NUMBER_OF_COLUMNS; ++i)
    {
        char letter = guess[i];
        GuessStatus status = verification[i];

        this->boxes[this->currentRow][i]->color(STATUS_COLORS[status]);

        if (status > this->letterStatuses[letter])
        {
            this->letterStatuses[letter] = status;
        }
        this->letterButtons[letter]->color(STATUS_COLORS[this->letterStatuses[letter]]);
        this->letterButtons[letter]->redraw();
    }

    this->currentColumn = 0;
    this->currentRow++;

    if (correctLetters == WordleMainWindow::NUMBER_OF_COLUMNS)
    {
        setWinState();
    }
    this->controller->clearGuess();
    updateGUI();
}

int WordleMainWindow::handleBackspace()
{
    if (this->controller->getGuess().size() > 0)
    {
        this->currentColumn--;
        this->getCurrentBox()->label("");
        this->controller->removeLetterFromGuess();

        if (this->currentColumn < 0)
        {
            this->currentColumn = 0;
        }
    }
}

int WordleMainWindow::handleLetterKeyPress(char key)
{
    if (this->controller->getGuess().size() < WORD_SIZE)
    {
        char output[1];
        output[0] = (char) key;

        this->controller->addLetterToGuess((char) key);
        this->getCurrentBox()->copy_label(output);
        this->currentColumn++;

        if (this->currentColumn > WordleMainWindow::NUMBER_OF_COLUMNS)
        {
            this->currentColumn = WordleMainWindow::NUMBER_OF_COLUMNS;
        }
    }
}

Fl_Box* WordleMainWindow::getCurrentBox()
{
    return this->boxes[this->currentRow][this->currentColumn];
}

void WordleMainWindow::updateGUI()
{
    for (int i = 0; i < WordleMainWindow::NUMBER_OF_ROWS; ++i)
    {
        for (int j = 0; j < WordleMainWindow::NUMBER_OF_COLUMNS; ++j)
        {
            this->boxes[i][j]->redraw();
        }
    }
}

void WordleMainWindow::setWinState()
{
    this->currentUser.addWin(this->currentRow + 1);
    this->winMessage->label("Congrats, you are winner.");
    this->currentRow = WordleMainWindow::NUMBER_OF_ROWS;
    this->currentColumn = WordleMainWindow::NUMBER_OF_COLUMNS;
}

void WordleMainWindow::cbLetterButtonPressed(Fl_Widget* widget, void* data)
{
    Fl_Button* button = (Fl_Button*) widget;
    WordleMainWindow* window = (WordleMainWindow*) data;
    window->handleLetterKeyPress(button->label()[0]);
}

void WordleMainWindow::cbEnterButtonPressed(Fl_Widget* widget, void* data)
{
    ((WordleMainWindow*)data)->handleEnter();
}

void WordleMainWindow::cbBackspaceButtonPressed(Fl_Widget* widget, void* data)
{
    ((WordleMainWindow*)data)->handleBackspace();
}
}
