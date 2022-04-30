#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

#include "UserAccount.h"

namespace model
{

class AccountManager
{
private:
    unordered_map<string, UserAccount> accounts;

public:
    AccountManager();
    virtual ~AccountManager();

    bool accountExists(const string& username);
    bool createAccount(const string& username);
    UserAccount& getAccount(const string& username);
    vector<string> getUsernames();

protected:
};

}
#endif // ACCOUNTMANAGER_H
