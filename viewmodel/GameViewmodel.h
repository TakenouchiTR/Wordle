#ifndef GAMEVIEWMODEL_H
#define GAMEVIEWMODEL_H

#define FILE_PATH "data.csv"
#define COLOR_PATH "colors.csv"

#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include <string>
#include <unordered_map>
using namespace std;

#include "WordleController.h"
using namespace controller;

#include "GuessStatus.h"

#include "AccountManager.h"
#include "ApplicationColors.h"
#include "UserAccount.h"
using namespace model;

namespace viewmodel
{

class GameViewmodel
{
private:
    Fl_Box* boxes[MAX_GUESSES][WORD_SIZE];
    Fl_Button* enterButton;
    Fl_Button* backspaceButton;

    bool playingGame;
    int currentRow;
    int currentColumn;
    unordered_map<char, Fl_Button*> letterButtons;
    unordered_map<char, GuessStatus> letterStatuses;

    WordleController* controller;
    AccountManager accountManager;
    UserAccount* currentUser;
    int colorIndex;
    ApplicationColors colors;

    Fl_Box* getCurrentBox();
    void setupDefaultColors();
    void resetUI();
    void handleWin();
    void handleLoss();
    void saveGame();
    void displayGameoverWindow(const string& title);

public:
    GameViewmodel();
    GameViewmodel(WordleController* controller);
    virtual ~GameViewmodel();
    void promptForAccount();
    void addLetter(char letter);
    void removeLetter();
    void makeGuess();
    void restartGame();
    void switchUsers();
    bool quitGame();
    void setBox(int row, int col, Fl_Box* box);
    void setLetterButton(char letter, Fl_Button* letterButton);
    void setEnterButton(Fl_Button* enterButton);
    void setBackspaceButton(Fl_Button* backspaceButton);

protected:
};

}

#endif // GAMEVIEWMODEL_H
