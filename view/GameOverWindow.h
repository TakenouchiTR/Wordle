#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Chart.H>

#include <string>
using namespace std;

#include "UserAccount.h"
using namespace model;

#include "DialogResult.h"

namespace view
{

class GameOverWindow : public Fl_Window
{
    private:
        Fl_Box* statisticsBox;
        Fl_Box* playedBox;
        Fl_Box* winPercentBox;
        Fl_Box* currentStreakBox;
        Fl_Box* maxStreakBox;
        Fl_Button* newGameButton;
        Fl_Button* switchUsersButton;
        Fl_Button* quitButton;
        Fl_Chart* statsChart;
        DialogResult result;

        void createStatisticsLabels(UserAccount *account);
        void createChart(UserAccount* account);
        void createButtons();

        void newGamePressed();
        void switchUsersPressed();
        void quitPressed();

        static void cbNewGamePressed(Fl_Widget* widget, void* data);
        static void cbSwitchUsersPressed(Fl_Widget* widget, void* data);
        static void cbQuitPressed(Fl_Widget* widget, void* data);

    public:
        GameOverWindow(UserAccount *account, const string& message);
        virtual ~GameOverWindow();

        DialogResult getResult();

    protected:
};

}

#endif // GAMEOVERWINDOW_H
