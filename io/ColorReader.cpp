#include "ColorReader.h"

#define COLOR_COUNT 4

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
using namespace std;

#include <stdexcept>
#include <string>
using namespace std;

#include "Utils.h"

namespace io
{

ColorReader::ColorReader()
{
    //ctor
}

ColorReader::~ColorReader()
{
    //dtor
}

ApplicationColors ColorReader::readFile(const string& filePath)
{
    if (!fileExists(filePath))
    {
        throw runtime_error("file \"" + filePath + "\" not found");
    }

    ApplicationColors applicationColors;
    ifstream fileStream(filePath);
    stringstream buffer;
    buffer << fileStream.rdbuf();

    vector<string> lines = splitString(buffer.str(), '\n');
    for (string line : lines)
    {
        try
        {
            vector<string> lineData = splitString(line, ',');
            vector<int> colors;

            string name = lineData[0];
            for (int i = 0; i < COLOR_COUNT; i++)
            {
                int color = toInt(lineData[i + 1], "Could not convert string to int");
                colors.push_back(color);
            }

            applicationColors.addColorSetting(name, colors);
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
    return applicationColors;
}

}
