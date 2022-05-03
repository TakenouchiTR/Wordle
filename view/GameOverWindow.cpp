#include "GameOverWindow.h"

#define WINDOW_WIDTH 360
#define WINDOW_HEIGHT 240

#include <sstream>
using namespace std;

#include "WordleController.h"
using namespace controller;

namespace view
{

GameOverWindow::GameOverWindow(UserAccount *account, const string& title)
    : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str())
{
    this->result = DialogResult::CANCELLED;

    begin();
    this->createStatisticsLabels(account);
    this->createChart(account);
    this->createButtons();
    end();
}

void GameOverWindow::createStatisticsLabels(UserAccount *account)
{
    const int STAT_Y = 40;
    const int STAT_HEIGHT = 40;

    stringstream statisticsStream;
    stringstream playedStream;
    stringstream percentStream;
    stringstream currentStreakStream;
    stringstream maxStreakStream;

    int winPercent =  account->getTotalWinCount() * 100 / account->getGamesPlayed();

    statisticsStream << account->getUsername() << "'s Statistics";
    playedStream << account->getGamesPlayed() << "\nPlayed";
    percentStream << winPercent << "%\nWin %";
    currentStreakStream << account->getCurrentWinStreak() << "\nCurrent\nStreak";
    maxStreakStream << account->getMaxWinStreak() << "\nMax\nStreak";

    this->statisticsBox = new Fl_Box(WINDOW_WIDTH / 2, 10, 0, 20, "");
    this->playedBox = new Fl_Box(WINDOW_WIDTH / 5, STAT_Y, 0, STAT_HEIGHT, "");
    this->winPercentBox = new Fl_Box(WINDOW_WIDTH / 5 * 2, STAT_Y, 0, STAT_HEIGHT, "");
    this->currentStreakBox = new Fl_Box(WINDOW_WIDTH / 5 * 3, STAT_Y + 8, 0, STAT_HEIGHT, "");
    this->maxStreakBox = new Fl_Box(WINDOW_WIDTH / 5 * 4, STAT_Y + 8, 0, STAT_HEIGHT, "");

    this->statisticsBox->copy_label(statisticsStream.str().c_str());
    this->playedBox->copy_label(playedStream.str().c_str());
    this->winPercentBox->copy_label(percentStream.str().c_str());
    this->currentStreakBox->copy_label(currentStreakStream.str().c_str());
    this->maxStreakBox->copy_label(maxStreakStream.str().c_str());

    this->statisticsBox->align(FL_ALIGN_CENTER);
    this->playedBox->align(FL_ALIGN_CENTER);
    this->winPercentBox->align(FL_ALIGN_CENTER);
    this->currentStreakBox->align(FL_ALIGN_CENTER);
    this->maxStreakBox->align(FL_ALIGN_CENTER);
}

void GameOverWindow::createChart(UserAccount* account)
{
    this->statsChart = new Fl_Chart(20, 100, WINDOW_WIDTH - 40, 80, "Guess Count Distribution");
    this->statsChart->type(FL_HORBAR_CHART);

    int maxBound = 1;
    for (int moves = 1; moves <= MAX_GUESSES; moves++)
    {
        if (account->getWinCount(moves) > maxBound)
        {
            maxBound = account->getWinCount(moves);
        }

        stringstream labelStream;
        labelStream << moves << "(" << account->getWinCount(moves) << ")";
        this->statsChart->add(account->getWinCount(moves), labelStream.str().c_str(), FL_DARK3);
    }
    this->statsChart->bounds(0, maxBound);
}

void GameOverWindow::createButtons()
{
    const int BUTTON_Y = 210;
    const int BUTTON_HEIGHT = 20;
    const int BUTTON_WIDTH = WINDOW_WIDTH / 4;
    this->newGameButton = new Fl_Button(20, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "New Game");
    this->mainMenuButton = new Fl_Button((WINDOW_WIDTH - BUTTON_WIDTH - 5) / 2, BUTTON_Y,
        BUTTON_WIDTH + 10, BUTTON_HEIGHT, "Main Menu"
    );
    this->quitButton = new Fl_Button(WINDOW_WIDTH - BUTTON_WIDTH - 20, BUTTON_Y, BUTTON_WIDTH,
        BUTTON_HEIGHT, "Quit"
    );

    this->newGameButton->callback(cbNewGamePressed, this);
    this->mainMenuButton->callback(cbMainMenuPressed, this);
    this->quitButton->callback(cbQuitPressed, this);
}

GameOverWindow::~GameOverWindow()
{
    delete(this->statisticsBox);
    delete(this->playedBox);
    delete(this->winPercentBox);
    delete(this->currentStreakBox);
    delete(this->maxStreakBox);
    delete(this->statsChart);
    delete(this->quitButton);
    delete(this->newGameButton);
    delete(this->mainMenuButton);
}

DialogResult GameOverWindow::getResult()
{
    return this->result;
}

void GameOverWindow::newGamePressed()
{
    this->result = DialogResult::PRIMARY;
    this->hide();
}

void GameOverWindow::mainMenuPressed()
{
    this->result = DialogResult::SECONDARY;
    this->hide();
}

void GameOverWindow::quitPressed()
{
    this->result = DialogResult::TERTIARY;
    this->hide();
}

void GameOverWindow::cbNewGamePressed(Fl_Widget* widget, void* data)
{
    ((GameOverWindow*) data)->newGamePressed();
}

void GameOverWindow::cbMainMenuPressed(Fl_Widget* widget, void* data)
{
    ((GameOverWindow*) data)->mainMenuPressed();
}

void GameOverWindow::cbQuitPressed(Fl_Widget* widget, void* data)
{
    ((GameOverWindow*) data)->quitPressed();
}

}
