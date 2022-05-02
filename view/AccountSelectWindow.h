#ifndef ACCOUNTSELECTWINDOW_H
#define ACCOUNTSELECTWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Window.H>

#include <string>
#include <vector>
using namespace std;

#include "AccountManager.h"
using namespace model;

#include "DialogResult.h"

#include "ApplicationColors.h"
using namespace utils;

namespace view
{

class AccountSelectWindow : public Fl_Window
{
private:
    AccountManager* accountManager;
    UserAccount* selectedAccount;
    vector<string> usernames;
    DialogResult result;
    Fl_Choice* nameChoice;
    Fl_Choice* colorBlindChoice;
    Fl_Check_Button* uniqueLetterCheckButton;
    Fl_Button* selectButton;
    Fl_Button* newButton;

    ApplicationColors::ColorBlindnessOption colorBlindess;

    void updateSelectedAccount();
    void nameChoiceSelectionChanged();
    void colorBlindChoiceSelectionChanged();
    void uniqueLetterCheckButtonPressed();
    void selectButtonPressed();
    void newButtonPressed();

    static void cbNameChoiceSelectionChanged(Fl_Widget* widget, void* data);
    static void cbColorBlindChoiceSelectionChanged(Fl_Widget* widget, void* data);
    static void cbUniqueLetterCheckButtonPressed(Fl_Widget* widget, void* data);
    static void cbSelectButtonPressed(Fl_Widget* widget, void* data);
    static void cbNewButtonPressed(Fl_Widget* widget, void* data);

public:
    AccountSelectWindow(AccountManager* accountManager);
    virtual ~AccountSelectWindow();

    UserAccount& getAccount();
    DialogResult getResult();
    ApplicationColors::ColorBlindnessOption getColorBlindnessIndex();

protected:

};

}

#endif // ACCOUNTSELECTWINDOW_H
