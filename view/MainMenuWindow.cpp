#include "MainMenuWindow.h"

#define WINDOW_WIDTH 240
#define WINDOW_HEIGHT 155

#include <FL/fl_ask.H>

#include <stdexcept>
#include <iostream>
using namespace std;

#include "ApplicationColors.h"
#include "UserAccount.h"
using namespace model;

namespace view
{
/**
    Creates an instance of AccountSelectionWindow using a specified AccountManager.

    Precondition: None
    Postcondition: this->getResult() == DialogResult::CANCELLED &&
                   this->getAccount() is a "random" account in accountManager if accounts
                        exist, otherwise it is null.
 */
MainMenuWindow::MainMenuWindow(AccountManager* accountManager, vector<string> colorChoices)
    : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Main Menu")
{
    this->accountManager = accountManager;
    this->usernames = accountManager->getUsernames();
    this->result = DialogResult::CANCELLED;
    this->selectedAccount = 0;

    begin();
    this->createWidgets();
    this->createCallbacks();

    for (const string& username : this->usernames)
    {
        this->nameChoice->add(username.c_str());
    }

    for (string color : colorChoices)
    {
        this->colorChoice->add(color.c_str());
    }

    this->colorChoice->value(0);

    if (this->usernames.size() > 0)
    {
        this->nameChoice->value(0);
        this->updateSelectedAccount();
    }
    end();
}

MainMenuWindow::~MainMenuWindow()
{
    delete(this->nameChoice);
    delete(this->uniqueLetterCheckButton);
    delete(this->selectButton);
    delete(this->newButton);
    delete(this->colorChoice);
    delete(this->quitButton);
}

void MainMenuWindow::createWidgets()
{
    this->nameChoice = new Fl_Choice(55, 20, 165, 20, "User");
    this->colorChoice = new Fl_Choice(55, 60, 165, 20, "Color");
    this->uniqueLetterCheckButton = new Fl_Check_Button(20, 90, 200, 20, "Use only unique letters");
    this->selectButton = new Fl_Button(20, 120, 60, 20, "Select");
    this->newButton = new Fl_Button(90, 120, 60, 20, "New");
    this->quitButton = new Fl_Button(160, 120, 60, 20, "Quit");
}

void MainMenuWindow::createCallbacks()
{
    this->nameChoice->callback(cbNameChoiceSelectionChanged, this);
    this->colorChoice->callback(cbColorChoiceSelectionChanged, this);
    this->uniqueLetterCheckButton->callback(cbUniqueLetterCheckButtonPressed, this);
    this->selectButton->callback(cbSelectButtonPressed, this);
    this->newButton->callback(cbNewButtonPressed, this);
    this->quitButton->callback(cbQuitButtonPressed, this);
}

void MainMenuWindow::updateSelectedAccount()
{
    string username = this->usernames[this->nameChoice->value()];
    this->selectedAccount = this->accountManager->getAccount(username);
    this->uniqueLetterCheckButton->value(this->selectedAccount->isUsingUniqueLetters());
    this->colorChoice->value(this->selectedAccount->getColorOption());
}

void MainMenuWindow::nameChoiceSelectionChanged()
{
    this->updateSelectedAccount();
}

void MainMenuWindow::colorChoiceSelectionChanged()
{
    if (this->selectedAccount == 0)
    {
        return;
    }
    this->selectedAccount->setColorOption(this->colorChoice->value());
}

void MainMenuWindow::uniqueLetterCheckButtonPressed()
{
    if (this->selectedAccount == 0)
    {
        return;
    }
    this->selectedAccount->setUsingUniqueLetters((bool)this->uniqueLetterCheckButton->value());
}

void MainMenuWindow::selectButtonPressed()
{
    if (this->selectedAccount == 0)
    {
        fl_alert("No account selected.\nPlease create an account to continue.");
        return;
    }
    this->result = DialogResult::PRIMARY;
    this->hide();
}

void MainMenuWindow::newButtonPressed()
{
    const char* result = fl_input("Enter a username");

    if (result == 0)
    {
        return;
    }

    if (result[0] == 0)
    {
        fl_alert("Username cannot be blank.");
        return;
    }

    if (this->accountManager->accountExists(result))
    {
        fl_alert("Account with username %s already exists", result);
        return;
    }

    this->accountManager->createAccount(result);
    this->usernames.push_back(result);
    this->nameChoice->add(result);
    this->nameChoice->value(this->usernames.size() - 1);
    this->updateSelectedAccount();
}

void MainMenuWindow::quitButtonPressed()
{
    this->result = DialogResult::SECONDARY;
    this->hide();
}

/**
    Gets the selected account.

    Precondition: An account has been selected.
    Postcondition: None

    Return: The selected account.
 */
UserAccount* MainMenuWindow::getAccount()
{
    if (this->selectedAccount == 0)
    {
        throw runtime_error("No accounts have been created.");
    }
    return this->selectedAccount;
}

/**
    Gets the result for the window.

    Precondition: None
    Postcondition: None

    Return: The result for the window.
 */
DialogResult MainMenuWindow::getResult()
{
    return this->result;
}

void MainMenuWindow::cbNameChoiceSelectionChanged(Fl_Widget* widget, void* data)
{
    ((MainMenuWindow*) data)->nameChoiceSelectionChanged();
}

void MainMenuWindow::cbUniqueLetterCheckButtonPressed(Fl_Widget* widget, void* data)
{
    ((MainMenuWindow*) data)->uniqueLetterCheckButtonPressed();
}

void MainMenuWindow::cbSelectButtonPressed(Fl_Widget* widget, void* data)
{
    ((MainMenuWindow*) data)->selectButtonPressed();
}

void MainMenuWindow::cbNewButtonPressed(Fl_Widget* widget, void* data)
{
    ((MainMenuWindow*) data)->newButtonPressed();
}

void MainMenuWindow::cbQuitButtonPressed(Fl_Widget* widget, void* data)
{
    ((MainMenuWindow*) data)->quitButtonPressed();
}

void MainMenuWindow::cbColorChoiceSelectionChanged(Fl_Widget* widget, void* data)
{
    ((MainMenuWindow*) data)->colorChoiceSelectionChanged();
}

}
