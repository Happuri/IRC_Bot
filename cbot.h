#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

class cBot
{
public:
    cBot(string filename);                  // open file to read
    void tailF();                           // equivalent "tail -f" bash command, notify if new user joins
    void displayFile(fstream &file);        // displays contents of file

private:
    int checkLenght(fstream &file);         // returns numbers of characters in file
    string filename;                        // name of file to read
};


