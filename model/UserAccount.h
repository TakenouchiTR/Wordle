#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#define MOVE_COUNT 6

#include <string>
using namespace std;

namespace model
{

class UserAccount
{
private:
    string username;
    int gamesPlayed;
    int currentWinStreak;
    int maxWinStreak;
    int winMoveDistribution[MOVE_COUNT];
    bool useUniqueLetters;

public:
    /**
    Creates an instance of UserAccount.

        Precondition: None
        Postcondition:
            this->getUsername() == "" &&
            this->getGamesPlayed() == 0 &&
            this->getCurrentWinStreak() == 0 &&
            this->getMaxWinStream() == 0 &&
            this->isUsingUniqueLetters() == true &&
            this->getWinCount(<moves>) == 0 for all moves 1-6, inclusive
    */
    UserAccount() : UserAccount("") {};
    UserAccount(const string& username);
    virtual ~UserAccount();

    void addWin(int moves);
    void addLoss();
    const string& getUsername();
    void setUsername(const string& username);
    int getGamesPlayed();
    void setGamesPlayed(int count);
    int getCurrentWinStreak();
    void setCurrentWinStreak(int streak);
    int getMaxWinStreak();
    void setMaxWinStreak(int streak);
    bool isUsingUniqueLetters();
    void setUsingUniqueLetters(bool useUniqueLetters);
    int getWinCount(int moves);
    void setWinCount(int moves, int wins);
    int getTotalWinCount();
    int getLossCount();

protected:
};

}
#endif // USERACCOUNT_H
