#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include "DialogResult.h"

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Window.H>

#include <string>
#include <vector>
using namespace std;

#include "AccountManager.h"
#include "ApplicationColors.h"
using namespace model;

namespace view
{

class MainMenuWindow : public Fl_Window
{
private:
    AccountManager* accountManager;
    UserAccount* selectedAccount;
    vector<string> usernames;
    DialogResult result;
    Fl_Choice* nameChoice;
    Fl_Choice* colorChoice;
    Fl_Check_Button* uniqueLetterCheckButton;
    Fl_Button* selectButton;
    Fl_Button* newButton;
    Fl_Button* quitButton;

    void createWidgets();
    void createCallbacks();

    void updateSelectedAccount();
    void nameChoiceSelectionChanged();
    void colorChoiceSelectionChanged();
    void uniqueLetterCheckButtonPressed();
    void selectButtonPressed();
    void newButtonPressed();
    void quitButtonPressed();

    static void cbNameChoiceSelectionChanged(Fl_Widget* widget, void* data);
    static void cbColorChoiceSelectionChanged(Fl_Widget* widget, void* data);
    static void cbUniqueLetterCheckButtonPressed(Fl_Widget* widget, void* data);
    static void cbSelectButtonPressed(Fl_Widget* widget, void* data);
    static void cbNewButtonPressed(Fl_Widget* widget, void* data);
    static void cbQuitButtonPressed(Fl_Widget* widget, void* data);

public:
    MainMenuWindow(AccountManager* accountManager, vector<string> colorChoices);
    virtual ~MainMenuWindow();

    UserAccount *getAccount();
    DialogResult getResult();

protected:

};

}

#endif // MAINMENUWINDOW_H
