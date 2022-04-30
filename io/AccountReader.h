#ifndef ACCOUNTREADER_H
#define ACCOUNTREADER_H

#include <string>
#include <vector>
using namespace std;

#include "AccountManager.h"
using namespace model;

namespace io
{

class AccountReader
{
private:
    vector<string> splitString(const string& text, const char delimiter);

public:
    AccountReader();
    virtual ~AccountReader();
    AccountManager readFile(const string& filePath);

protected:
};

}

#endif // ACCOUNTREADER_H
