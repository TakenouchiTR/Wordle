#include "GameViewmodel.h"

#include <FL/fl_ask.H>

#include <iostream>
#include <stdexcept>
#include <unistd.h>
using namespace std;

#include "AccountReader.h"
#include "AccountWriter.h"
#include "ColorReader.h"
using namespace io;

#include "AccountSelectWindow.h"
#include "GameOverWindow.h"
using namespace view;

#include "Utils.h"

namespace viewmodel
{

/**
    Creates an instance of GameViewmodel.

    Precondition: None
    Postcondition: None
 */
GameViewmodel::GameViewmodel()
{
    //ctor
}

/**
    Creates an instance of GameViewmodel with a specified Wordle game.

    Precondition: controller != 0
    Postcondition: None

    Params:
        controller - The controller for the Wordle game
 */
GameViewmodel::GameViewmodel(WordleController* controller)
{
    if (controller == 0)
    {
        throw runtime_error("controller must not be null");
    }

    this->playingGame = false;
    this->controller = controller;
    this->currentRow = 0;
    this->currentColumn = 0;
    this->colorIndex = 0;

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
    if (fileExists(COLOR_PATH))
    {
        try
        {
            ColorReader reader;
            this->colors = reader.readFile(COLOR_PATH);
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
    else
    {
        this->setupDefaultColors();
    }
}

GameViewmodel::~GameViewmodel()
{
    delete this->controller;
}

void GameViewmodel::setupDefaultColors()
{
    this->colors.addColorSetting("Normal", {FL_GRAY, FL_DARK2, FL_YELLOW, FL_GREEN});
    this->colors.addColorSetting("Deuteranopia", {FL_GRAY, FL_DARK2, 124, 175});
    this->colors.addColorSetting("Protanopia", {FL_GRAY, FL_DARK2, 84, FL_YELLOW});
    this->colors.addColorSetting("Tritanopia", {FL_GRAY, FL_DARK2, 253, 191});
}

/**
    Attempts to add a letter to the guess, if the guess isn't already at the max length.

    Precondition: None
    Postcondition: The letter is added to the guess if the guess' length is < WORD_SIZE

    Params:
        letter - The letter to add.
 */
void GameViewmodel::addLetter(char letter)
{
    if (this->currentRow < MAX_GUESSES && this->controller->getGuess().size() < WORD_SIZE)
    {
        char output[1];
        output[0] = letter;

        this->controller->addLetterToGuess(letter);
        this->getCurrentBox()->copy_label(output);
        this->currentColumn++;

        if (this->currentColumn > WORD_SIZE)
        {
            this->currentColumn = WORD_SIZE;
        }
    }
}

/**
    Attempts to remove a letter from the guess, if the guess isn't empty.

    Precondition: None
    Postcondition: The last letter is removed from the guess if the guess isn't empty.
 */
void GameViewmodel::removeLetter()
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

/**
    Attempts to check if the guess is correct.

    Precondition: None
    Postcondition: A guess is made if the guess is of size WORD_LENGTH and it exists in the
                   Wordle dictionary.
 */
void GameViewmodel::makeGuess()
{
    if (!this->controller->isGuessInDictionary())
    {
        if (this->controller->getGuess().size() == WORD_SIZE)
        {
            fl_alert("\"%s\" is not a known word.", this->controller->getGuess().c_str());
        }
        return;
    }

    GuessStatus* verification = this->controller->evaluateGuess();
    string guess = this->controller->getGuess();
    int correctLetters = 0;

    for (int i = 0; i < WORD_SIZE; ++i)
    {
        char letter = guess[i];
        GuessStatus status = verification[i];

        if (verification[i] == GuessStatus::CORRECT_POSITION)
        {
            correctLetters++;
        }

        this->boxes[this->currentRow][i]->color(this->colors.getColors()[this->colorIndex][status]);
        this->boxes[this->currentRow][i]->redraw();

        if (status > this->letterStatuses[letter])
        {
            this->letterStatuses[letter] = status;
        }

        this->letterButtons[letter]->color(this->colors.getColors()[this->colorIndex][this->letterStatuses[letter]]);
        this->letterButtons[letter]->redraw();
    }

    this->currentColumn = 0;
    this->currentRow++;

    if (correctLetters == WORD_SIZE)
    {
        this->handleWin();
    }
    else if (currentRow == MAX_GUESSES)
    {
        this->handleLoss();
    }
    this->controller->clearGuess();
}

/**
    Asks if the user wishes to end the current game and start a new one. If answered yes, then
    a loss is added to the user's account and a new game is started.

    Precondition: None
    Postcondition: If the user chooses to restart, a loss is added to their account and the a new
                   game is started; otherwise None.
 */
void GameViewmodel::restartGame()
{
    int selectedOption = fl_choice(
        "Are you sure you would you restart the game?\nRestarting a game will give you a new word and count as a loss.",
        "Restart Game",
        "Continue Game",
        0
    );
    if (selectedOption == 0)
    {
        this->currentUser->addLoss();
        this->saveGame();
        this->resetUI();
        this->controller->selectNewWord();
    }
}

/**
    Asks if the user wishes to end the current game to switch to a new user. If answered yes, then
    a loss is added to the user's account and the account selection screen is shown.

    Precondition: None
    Postcondition: If the user chooses to switch users, a loss is added to their account and the select
                   user screen is shown; otherwise None.
 */
void GameViewmodel::switchUsers()
{
    int selectedOption = fl_choice(
        "Are you sure you would you like to switch users?\nSwitching users during a game will count as a loss.",
        "Switch Users",
        "Continue Game",
        0
    );
    if (selectedOption == 0)
    {
        this->currentUser->addLoss();
        this->saveGame();
        this->resetUI();
        this->promptForAccount();
    }
}

/**
    Attempts to close the application. If a game is running, it prompts the user if they wish to quit
    the game. If the user chooses to quit and is in a game, then a loss is added to their account.

    Precondition: None
    Postcondition: None

    Return: Whether the user chose to quit the application.
 */
bool GameViewmodel::quitGame()
{
    if (!this->playingGame)
    {
        return true;
    }

    int dialogResult = fl_choice(
        "Are you sure you want to quit the application?\nYour current game will count as a loss.",
        "Quit",
        "Continue Game",
        0
    );

    if (dialogResult == 0)
    {
        this->currentUser->addLoss();
        this->saveGame();
    }

    return dialogResult == 0;
}

/**
    Displays the game over screen, informs the user that they have won, updates their
    statistics, and prevents any further input.

    Precondition: None
    Postcondition: The game over screen is displayed.
 */
void GameViewmodel::handleWin()
{
    this->currentUser->addWin(this->currentRow);
    this->currentRow = MAX_GUESSES;
    this->currentColumn = WORD_SIZE;

    this->saveGame();

    this->displayGameoverWindow("You won!");
}

/**
    Displays the game over screen, informs the user that they have lost, updates their
    statistics, and prevents any further input.

    Precondition: None
    Postcondition: The game over screen is displayed.
 */
void GameViewmodel::handleLoss()
{
    this->currentUser->addLoss();
    this->currentRow = MAX_GUESSES;
    this->currentColumn = WORD_SIZE;

    this->saveGame();

    this->displayGameoverWindow("Game Over");
}

void GameViewmodel::displayGameoverWindow(const string& title)
{
    this->answerBox->copy_label(this->controller->getCurrentWord().c_str());
    this->answerBox->redraw();

    this->playingGame = false;
    GameOverWindow window(this->currentUser, title);
    window.set_modal();

    while (window.getResult() == DialogResult::CANCELLED)
    {
        window.show();
        while(window.shown())
        {
            Fl::wait();
        }
    }

    this->resetUI();

    if (window.getResult() == DialogResult::PRIMARY)
    {
        this->controller->selectNewWord();
        this->playingGame = true;
    }
    else if (window.getResult() == DialogResult::SECONDARY)
    {
        this->promptForAccount();
    }
    else
    {
        exit(0);
    }
}

void GameViewmodel::resetUI()
{
    this->currentRow = 0;
    this->currentColumn = 0;
    int unknownColor = this->colors.getColors()[this->colorIndex][GuessStatus::UNKNOWN];

    for (int row = 0; row < MAX_GUESSES; row++)
    {
        for (int col = 0; col < WORD_SIZE; col++)
        {
            this->boxes[row][col]->copy_label("");
            this->boxes[row][col]->color(unknownColor);
        }
    }

    for (char letter = 'a'; letter <= 'z'; letter++)
    {
        this->letterButtons[letter]->color(unknownColor);
        this->letterStatuses[letter] = GuessStatus::UNKNOWN;
        this->letterButtons[letter]->redraw();
    }

    this->enterButton->color(unknownColor);
    this->backspaceButton->color(unknownColor);

    this->enterButton->redraw();
    this->backspaceButton->redraw();

    this->answerBox->copy_label("          ");
}

void GameViewmodel::saveGame()
{
    AccountWriter writer;
    writer.writeFile(FILE_PATH, this->accountManager);
}

/**
    Prompts the user to select an account.

    Precondition: None
    Postcondition: The game is set up to be played.
 */
void GameViewmodel::promptForAccount()
{
    AccountSelectWindow window(&this->accountManager, this->colors.getTitles());
    window.set_modal();
    while (window.getResult() == DialogResult::CANCELLED)
    {
        window.show();
        while(window.shown())
        {
            Fl::wait();
        }
    }

    if (window.getResult() == DialogResult::PRIMARY)
    {
        this->currentUser = window.getAccount();
        this->controller->setUsingUniqueLetters(this->currentUser->isUsingUniqueLetters());
        this->controller->selectNewWord();
        this->colorIndex = this->currentUser->getColorOption();

        AccountWriter writer;
        writer.writeFile(FILE_PATH, this->accountManager);
        this->playingGame = true;
    }
    else
    {
        exit(0);
    }
}

/**
    Sets the box that displays a letter in a guess at a specified row and column.

    Precondition: box != 0
    Postcondition: None

    Params:
        row - The row of the box.
        col - The column of the box.
        box - The box to set.
 */
void GameViewmodel::setBox(int row, int col, Fl_Box* box)
{
    if (box == 0)
    {
        throw runtime_error("box must not be null");
    }
    this->boxes[row][col] = box;
}

/**
    Sets the button for the on-screen keyboard for a specified character.

    Precondition: letterButton != 0
    Postcondition: None

    Params:
        letter - Which letter the button should handle.
        letterButton - The button to set.
 */
void GameViewmodel::setLetterButton(char letter, Fl_Button* letterButton)
{
    if (letterButton == 0)
    {
        throw runtime_error("letterButton must not be null");
    }
    this->letterButtons[letter] = letterButton;
    this->letterStatuses[letter] = GuessStatus::UNKNOWN;
}

/**
    Sets the button for the on-screen keyboard's enter.

    Precondition: letterButton != 0
    Postcondition: None

    Params:
        enterButton - The enter button.
 */
void GameViewmodel::setEnterButton(Fl_Button* enterButton)
{
    if (enterButton == 0)
    {
        throw runtime_error("enterButton must not be null");
    }

    this->enterButton = enterButton;
}

/**
    Sets the button for the on-screen keyboard's backspace.

    Precondition: letterButton != 0
    Postcondition: None

    Params:
        backspaceButton - The backspace button.
 */
void GameViewmodel::setBackspaceButton(Fl_Button* backspaceButton)
{
    if (backspaceButton == 0)
    {
        throw runtime_error("letterButton must not be null");
    }

    this->backspaceButton = backspaceButton;
}

void GameViewmodel::setAnswerBox(Fl_Box* answerBox)
{
    this->answerBox = answerBox;
}

Fl_Box* GameViewmodel::getCurrentBox()
{
    return this->boxes[this->currentRow][this->currentColumn];
}

}
