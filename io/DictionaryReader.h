#ifndef DICTIONARYREADER_H
#define DICTIONARYREADER_H

#include <string>
using namespace std;

#include "Dictionary.h"
using namespace model;

namespace io
{

class DictionaryReader
{
private:

public:
    DictionaryReader();
    virtual ~DictionaryReader();
    Dictionary readFile(int wordLength, const string& filePath);

protected:
};

}
#endif // DICTIONARYREADER_H
