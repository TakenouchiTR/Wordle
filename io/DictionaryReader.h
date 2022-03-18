#ifndef DICTIONARYREADER_H
#define DICTIONARYREADER_H

#include <unordered_set>
#include <string>
using namespace std;

namespace io
{

class DictionaryReader
{
    private:

    public:
        DictionaryReader();
        virtual ~DictionaryReader();
        unordered_set<string> readFile(int wordLength, const string& filePath);

    protected:
};

}
#endif // DICTIONARYREADER_H
