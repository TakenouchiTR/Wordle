#include "AccountReader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
using namespace std;

#include "UserAccount.h"
using namespace model;

#include "Utils.h"

namespace io
{

/**
    Creates an instance of AccountReader.

    Precondition: None
    Postcondition: None
 */
AccountReader::AccountReader()
{
    //ctor
}

AccountReader::~AccountReader()
{
    //dtor
}

/**
    Reads accounts from a file and returns them as an AccountManager.

    Precondition: fileExists(filePath)
    Postcondition: None

    Params:
        filePath - The path to the file.
    Return: An AccountManager containing all the accounts within the file.
 */
AccountManager AccountReader::readFile(const string& filePath)
{
    if (!fileExists(filePath))
    {
        throw runtime_error("file \"" + filePath + "\" not found");
    }

    AccountManager accountManager;
    ifstream fileStream(filePath);
    stringstream buffer;
    buffer << fileStream.rdbuf();

    vector<string> lines = splitString(buffer.str(), '\n');
    for (string line : lines)
    {
        try
        {
            vector<string> lineData = splitString(line, ',');
            int winDistribution[MOVE_COUNT];

            string username = lineData[0];
            int gamesPlayed = toInt(lineData[1], "Could not convert string to int");
            int currentWinStreak = toInt(lineData[2], "Could not convert string to int");
            int maxWinStreak = toInt(lineData[3], "Could not convert string to int");
            bool useUniqueLetters = toInt(lineData[4], "Could not convert string to int");
            int colorOption = toInt(lineData[5], "Could not convert string to int");
            for (int i = 0; i < MOVE_COUNT; i++)
            {
                winDistribution[i] = toInt(lineData[6 + i], "Could not convert string to int");
            }

            accountManager.createAccount(username);
            UserAccount* account = accountManager.getAccount(username);

            account->setGamesPlayed(gamesPlayed);
            account->setCurrentWinStreak(currentWinStreak);
            account->setMaxWinStreak(maxWinStreak);
            account->setUsingUniqueLetters(useUniqueLetters);
            account->setColorOption(colorOption);
            for (int i = 0; i < MOVE_COUNT; i++)
            {
                account->setWinCount(i + 1, winDistribution[i]);
            }
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
    return accountManager;
}

}
