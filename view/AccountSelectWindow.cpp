#include "AccountSelectWindow.h"

#define WINDOW_WIDTH 240
#define WINDOW_HEIGHT 135

#include <FL/fl_ask.H>

#include <stdexcept>
#include <iostream>
using namespace std;

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
AccountSelectWindow::AccountSelectWindow(AccountManager* accountManager) : Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "User Select")
{
    this->accountManager = accountManager;
    this->usernames = accountManager->getUsernames();
    this->result = DialogResult::CANCELLED;
    this->selectedAccount = 0;

    begin();
    this->nameChoice = new Fl_Choice(55, 20, 165, 20, "User");
    this->uniqueLetterCheckButton = new Fl_Check_Button(20, 50, 200, 20, "Use only unique letters");
    this->selectButton = new Fl_Button(20, 95, 80, 20, "Select");
    this->newButton = new Fl_Button(140, 95, 80, 20, "New");

    this->nameChoice->callback(cbNameChoiceSelectionChanged, this);
    this->uniqueLetterCheckButton->callback(cbUniqueLetterCheckButtonPressed, this);
    this->selectButton->callback(cbSelectButtonPressed, this);
    this->newButton->callback(cbNewButtonPressed, this);

    for (const string& username : this->usernames)
    {
        this->nameChoice->add(username.c_str());
    }

    if (this->usernames.size() > 0)
    {
        this->nameChoice->value(0);
        this->updateSelectedAccount();
    }
    end();
}

AccountSelectWindow::~AccountSelectWindow()
{
    delete(this->nameChoice);
    delete(this->uniqueLetterCheckButton);
    delete(this->selectButton);
    delete(this->newButton);
}

void AccountSelectWindow::updateSelectedAccount()
{
    string username = this->usernames[this->nameChoice->value()];
    this->selectedAccount = this->accountManager->getAccount(username);
    this->uniqueLetterCheckButton->value(this->selectedAccount->isUsingUniqueLetters());
}

void AccountSelectWindow::nameChoiceSelectionChanged()
{
    this->updateSelectedAccount();
}

void AccountSelectWindow::uniqueLetterCheckButtonPressed()
{
    if (this->selectedAccount == 0)
    {
        return;
    }
    this->selectedAccount->setUsingUniqueLetters((bool)this->uniqueLetterCheckButton->value());
}

void AccountSelectWindow::selectButtonPressed()
{
    if (this->selectedAccount == 0)
    {
        fl_alert("No account selected.\nPlease create an account to continue.");
        return;
    }
    this->result = DialogResult::PRIMARY;
    this->hide();
}

void AccountSelectWindow::newButtonPressed()
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

/**
    Gets the selected account.

    Precondition: An account has been selected.
    Postcondition: None

    Return: The selected account.
 */
UserAccount* AccountSelectWindow::getAccount()
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

    return: The result for the window.
 */
DialogResult AccountSelectWindow::getResult()
{
    return this->result;
}

void AccountSelectWindow::cbNameChoiceSelectionChanged(Fl_Widget* widget, void* data)
{
    ((AccountSelectWindow*) data)->nameChoiceSelectionChanged();
}

void AccountSelectWindow::cbUniqueLetterCheckButtonPressed(Fl_Widget* widget, void* data)
{
    ((AccountSelectWindow*) data)->uniqueLetterCheckButtonPressed();
}

void AccountSelectWindow::cbSelectButtonPressed(Fl_Widget* widget, void* data)
{
    ((AccountSelectWindow*) data)->selectButtonPressed();
}

void AccountSelectWindow::cbNewButtonPressed(Fl_Widget* widget, void* data)
{
    ((AccountSelectWindow*) data)->newButtonPressed();
}

}
