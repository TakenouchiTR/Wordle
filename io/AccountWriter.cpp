#include "AccountWriter.h"

#include <fstream>
#include <iostream>
using namespace std;

#include "UserAccount.h"
using namespace model;

#include "Utils.h"

namespace io
{
/**
    Creates an instance of AccountWriter.

    Precondition: None
    Postcondition: None
 */
AccountWriter::AccountWriter()
{
    //ctor
}

AccountWriter::~AccountWriter()
{
    //dtor
}

/**
    Writes the accounts in an AccountManager to a file.

    Precondition: None
    Postcondition: None

    Params:
        filePath - The path to the file.
        accountManager - The account manager to save.
 */
void AccountWriter::writeFile(const string& filePath, AccountManager& accountManager)
{
    ofstream fileStream(filePath);

    for (const string& username : accountManager.getUsernames())
    {
        UserAccount account = accountManager.getAccount(username);
        fileStream << account.getUsername() << ","
                   << account.getGamesPlayed() << ","
                   << account.getCurrentWinStreak() << ","
                   << account.getMaxWinStreak() << ","
                   << (int)account.isUsingUniqueLetters();
        for (unsigned int i = 1; i <= MOVE_COUNT; i++)
        {
            fileStream << "," << account.getWinCount(i);
        }
        fileStream << endl;
    }

    fileStream.close();
}

}
