#include "WordleMainWindow.h"

#include <string>
using namespace std;

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
 */
WordleMainWindow::WordleMainWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    this->currentRow = 0;
    this->currentColumn = 0;
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

int WordleMainWindow::handleBackspace()
{
    if (this->currentColumn >= 0)
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
    if (this->currentColumn < WordleMainWindow::NUMBER_OF_COLUMNS)
    {
        char output[1];
        output[0] = (char) key;
        this->getCurrentBox()->label(output);
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

WordleMainWindow::~WordleMainWindow()
{
    for (int i = 0; i < WordleMainWindow::NUMBER_OF_ROWS; ++i)
    {
        for (int j = 0; j < WordleMainWindow::NUMBER_OF_COLUMNS; ++j)
        {
            delete this->boxes[i][j];
        }
    }
}
}

