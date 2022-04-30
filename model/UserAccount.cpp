#include "UserAccount.h"

#include <stdexcept>
using namespace std;

namespace model
{
/**
    Creates an instance of UserAccount with a specified username.

    Precondition: None
    Postcondition:
        this->getUsername() == username &&
        this->getGamesPlayed() == 0 &&
        this->getCurrentWinStreak() == 0 &&
        this->getMaxWinStream() == 0 &&
        this->isUsingUniqueLetters() == true &&
        this->getWinCount(<moves>) == 0 for all moves 1-6, inclusive
 */
UserAccount::UserAccount(const string& username)
{
    this->username = username;
    this->gamesPlayed = 0;
    this->currentWinStreak = 0;
    this->maxWinStreak = 0;
    this->useUniqueLetters = true;

    for (unsigned int i = 0; i < MOVE_COUNT; i++)
    {
        this->winMoveDistribution[i] = 0;
    }
}

UserAccount::~UserAccount()
{
    //dtor
}

/**
    Adds a win to the account's statistics.

    Precondition: moves >= 1 && <= 6
    Postcondition: this->getWinCount(moves) == this->getWinCount(moves)@prev + 1 &&
                   this->getCurrentWinStreak() == this->getCurrentWinStreak@prev + 1 &&
                   this->getGamesPlayed() == this->getGamesPlayed()@prev + 1 &&
                   this->getMaxWinStreak() == max(this->getCurrentWinStreak(), this->getMaxWinStreak()@prev + 1)

    Params:
        moves - The number of moves to win.
 */
void UserAccount::addWin(int moves)
{
    this->setWinCount(moves, this->winMoveDistribution[moves] + 1);
    this->currentWinStreak++;
    this->gamesPlayed++;
    if (this->currentWinStreak > this->maxWinStreak)
    {
        this->maxWinStreak = this->currentWinStreak;
    }
}

/**
    Adds a loss to the account's statistics.

    Precondition: None
    Postcondition: this->getCurrentWinStreak() == 0 &&
                   this->getGamesPlayed() == this->getGamesPlayed()@prev + 1

    Params:
        moves - The number of moves to win.
 */
void UserAccount::addLoss()
{
    this->currentWinStreak = 0;
    this->gamesPlayed++;
}

/**
    Gets the account's username.

    Precondition: None
    Postcondition: None

    Return: The username.
 */
const string& UserAccount::getUsername()
{
    return this->username;
}

/**
    Sets the account's username.

    Precondition: None
    Postcondition: this->getUsername() == username

    Params:
        username - The username.
 */
void UserAccount::setUsername(const string& username)
{
    this->username = username;
}

/**
    Gets the number of games played.

    Precondition: None
    Postcondition: None

    Return: The number of games played.
 */
int UserAccount::getGamesPlayed()
{
    return this->gamesPlayed;
}

/**
    Sets the number of games played.

    Precondition: count >= 0
    Postcondition: this->getGamesPlayed() == count

    Params:
        count - The number of games played
 */
void UserAccount::setGamesPlayed(int count)
{
    if (count < 0)
    {
        throw runtime_error("Count must not be negative");
    }
    this->gamesPlayed = count;
}

/**
    Gets the current win streak.

    Precondition: None
    Postcondition: None

    Return: The current win streak.
 */
int UserAccount::getCurrentWinStreak()
{
    return this->currentWinStreak;
}

/**
    Sets the current win streak.

    Precondition: streak >= 0
    Postcondition: this->getCurrentWinStreak() == streak

    Params:
        streak - The current win streak
 */
void UserAccount::setCurrentWinStreak(int streak)
{
    if (streak < 0)
    {
        throw runtime_error("streak must not be negative.");
    }
    this->currentWinStreak = streak;
}

/**
    Gets the highest win streak.

    Precondition: None
    Postcondition: None

    Return: The highest win streak.
 */
int UserAccount::getMaxWinStreak()
{
    return this->maxWinStreak;
}

/**
    Sets the highest win streak.

    Precondition: streak >= 0
    Postcondition: this->getMaxWinStreak() == streak

    Params:
        count - The highest win streak.
 */
void UserAccount::setMaxWinStreak(int streak)
{
    if (streak < 0)
    {
        throw runtime_error("streak must not be negative");
    }
    this->maxWinStreak = streak;
}

/**
    Gets whether the account is set to only use words with unique letters.

    Precondition: None
    Postcondition: None

    Return: Whether the account will only use words with unique letters.
 */
bool UserAccount::isUsingUniqueLetters()
{
    return this->useUniqueLetters;
}

/**
    Sets whether the account is set to only use words with unique letters.

    Precondition: None
    Postcondition: this->isUsingUniqueLetters() == useUniqueLetters

    Params:
        useUniqueLetters - Whether to only use words with unique letters.
 */
void UserAccount::setUsingUniqueLetters(bool useUniqueLetters)
{
    this->useUniqueLetters = useUniqueLetters;
}

/**
    Gets the number of times the account has won with a specified number of moves.

    Precondition: None
    Postcondition: None

    Return: The number of games played.
 */
int UserAccount::getWinCount(int moves)
{
    return this->winMoveDistribution[moves - 1];
}

/**
    Sets the number of times the account has won with a specified number of moves.

    Precondition: moves >= 1 && moves <= 6 &&
                  wins >= 0
    Postcondition: this->getWinCount(moves) == wins

    Param:
        moves - The number of moves the player won with.
        wins - How many times the player won with the specified move count.
 */
void UserAccount::setWinCount(int moves, int wins)
{
    if (moves <= 0 || moves > MOVE_COUNT)
    {
        throw runtime_error("moves must be a number between 1 and " + MOVE_COUNT);
    }
    if (wins < 0)
    {
        throw runtime_error("wins must not be negative.");
    }
    this->winMoveDistribution[moves - 1] = wins;
}

/**
    Gets the total number of games won.

    Precondition: None
    Postcondition: None

    Return: The total number of games won.
 */
int UserAccount::getTotalWinCount()
{
    int totalWins = 0;
    for (int wins : this->winMoveDistribution)
    {
        totalWins += wins;
    }
    return totalWins;
}

/**
    Gets the number of games lost.

    Precondition: None
    Postcondition: None

    Return: The number of games lost.
 */
int UserAccount::getLossCount()
{
    return this->gamesPlayed - this->getTotalWinCount();
}

}
