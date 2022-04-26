#include "WordleMainWindow.h"

#include <string>
#include <iostream>
using namespace std;

#include "WordleController.h"
#include "GuessStatus.h"
using namespace controller;

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
    this->currentRow = 0;
    this->currentColumn = 0;
    this->controller = controller;
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
    this->winMessage = new Fl_Box(FL_NO_BOX, 250, 50, 200, 50, "");
    end();
}

int WordleMainWindow::handle(int event)
{
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
        handleLetterKeyPress(key);
    }
}

int WordleMainWindow::handleEnter()
{
    if (this->currentRow < WordleMainWindow::NUMBER_OF_ROWS && this->currentColumn == WordleMainWindow::NUMBER_OF_COLUMNS - 1)
    {
        string output;
        for (int i = 0; i < WordleMainWindow::NUMBER_OF_COLUMNS; ++i)
        {
            output += this->currentWord[i];
        }
        GuessStatus* verification = this->controller->evaluateGuess(output);
        int correctLetters = 0;
        for (int i = 0; i < WordleMainWindow::NUMBER_OF_COLUMNS; ++i)
        {
            switch(verification[i])
            {
            case GuessStatus::CORRECT_POSITION:
                this->boxes[this->currentRow][i]->color(63);
                correctLetters++;
                break;
            case GuessStatus::INCORRECT_POSITION:
                this->boxes[this->currentRow][i]->color(95);
            break;
            case GuessStatus::DOES_NOT_EXIST:
                this->boxes[this->currentRow][i]->color(45);
                break;
            }
        }

        this->currentColumn = 0;
        this->currentRow++;

        if (correctLetters == WordleMainWindow::NUMBER_OF_COLUMNS)
        {
            setWinState();
        }
        updateGUI();
    }
}

int WordleMainWindow::handleBackspace()
{
    if (this->currentColumn >= 0 && this->currentRow < WordleMainWindow::NUMBER_OF_ROWS)
    {
        this->getCurrentBox()->label("");

        this->currentColumn--;
        if (this->currentColumn < 0)
        {
            this->currentColumn = 0;
        }
    }
}

int WordleMainWindow::handleLetterKeyPress(int key)
{
    if (this->currentColumn < WordleMainWindow::NUMBER_OF_COLUMNS && this->currentRow < WordleMainWindow::NUMBER_OF_ROWS)
    {
        char output[1];
        output[0] = (char) key;
        this->currentWord[this->currentColumn] = (char) key;
        this->getCurrentBox()->copy_label(output);
        this->currentColumn++;
        if (this->currentColumn >= WordleMainWindow::NUMBER_OF_COLUMNS)
        {
            this->currentColumn = WordleMainWindow::NUMBER_OF_COLUMNS - 1;
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
    this->winMessage->label("Congrats, you are winner.");
    this->currentRow = WordleMainWindow::NUMBER_OF_ROWS;
    this->currentColumn = WordleMainWindow::NUMBER_OF_COLUMNS;
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
}

