#ifndef ACCOUNTWRITER_H
#define ACCOUNTWRITER_H

#include <string>
using namespace std;

#include "AccountManager.h"
using namespace model;

namespace io
{

class AccountWriter
{
    private:

    public:
        AccountWriter();
        virtual ~AccountWriter();
        void writeFile(const string& filePath, AccountManager& accountManager);

    protected:
};

}

#endif // ACCOUNTWRITER_H
