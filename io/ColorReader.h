#ifndef COLORREADER_H
#define COLORREADER_H

#include "ApplicationColors.h"
using namespace model;

namespace io
{

class ColorReader
{
private:

public:
    ColorReader();
    virtual ~ColorReader();

    ApplicationColors readFile(const string& filePath);

protected:
};

}

#endif // COLORREADER_H
