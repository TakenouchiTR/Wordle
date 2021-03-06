#include "GameWindow.h"
using namespace view;

#include "GuessStatus.h"
#include "WordleGame.h"
#include "Dictionary.h"
using namespace model;

#include "DictionaryReader.h"
using namespace io;

int main (int argc, char ** argv)
{
    DictionaryReader reader;
    auto words = reader.readFile(5, "dictionary.txt");
    Dictionary dictionary(words);
    WordleGame* controller = new WordleGame(&words);

    GameWindow window(380, 410, "Team C's Wordle Application", controller);
    window.show();

    int exitCode = Fl::run();
    return exitCode;
}
