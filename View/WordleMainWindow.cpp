#include "WordleMainWindow.h"

#include <iostream>
#include <string>
using namespace std;

namespace view
{
WordleMainWindow::WordleMainWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    this->currentRow = 0;
    this->currentColumn = 0;
    begin();
    int boxYPosition = 25;
    int boxSquareSize = 40;
    int xIncrement = boxSquareSize + 15;
    int yIncrement = boxSquareSize + 20;
    for (int i = 0; i < WordleMainWindow::NUMBER_OF_ROWS; ++i)
    {
        int boxXPosition = 100;
        for (int j = 0; j < WordleMainWindow::NUMBER_OF_COLUMNS; ++j)
        {
            Fl_Box* box = new Fl_Box(boxXPosition, boxYPosition, boxSquareSize, boxSquareSize, "A");
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
        return handleKeyDown(event,Fl::event_key());
    }
}

int WordleMainWindow::handleKeyDown(int event, int key)
{
    if (key == FL_Enter)
    {

    }
    if (key == FL_BackSpace)
    {
        if (this->currentColumn > -1)
        {
            this->getCurrentBox()->label("");

            this->currentColumn--;
            if (this->currentColumn < 0)
            {
                this->currentColumn = 0;
            }
        }
    }
    if (key >= 'a' && key <= 'z')
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

