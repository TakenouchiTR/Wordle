#include "AccountManager.h"

#include <stdexcept>
using namespace std;

namespace model
{

/**
    Creates an instance of AccountManager.

    Precondition: None
    Postcondition: this->getUsernames().size() == 0
 */
AccountManager::AccountManager()
{
    //ctor
}

AccountManager::~AccountManager()
{
    //dtor
}

/**
    Checks if an account with the specified username exists.

    Precondition: None
    Postcondition: None

    Params:
        username - The username to check.
    Return: Whether an account with the username exists.
 */
bool AccountManager::accountExists(const string& username)
{
    return this->accounts.find(username) != this->accounts.end();
}

/**
    Attempts to create an account with the specified username and returns the result. If an
    account already exists, no action is taken and false is returned. Otherwise, the account
    is created and true is returned.

    Precondition: None
    Postcondition: None

    Params:
        username - The username to check.
    Return: Whether an account with the username exists.
 */
bool AccountManager::createAccount(const string& username)
{
    if (this->accountExists(username))
    {
        return false;
    }
    this->accounts[username] = UserAccount(username);
    return true;
}

UserAccount& AccountManager::getAccount(const string& username)
{
    if (!this->accountExists(username))
    {
        throw runtime_error("username \"" + username + "\" not found");
    }
    return this->accounts[username];
}

vector<string> AccountManager::getUsernames()
{
    vector<string> keys;
    for (const auto &iter : this->accounts)
    {
        keys.push_back(iter.first);
    }
    return keys;
}

}
