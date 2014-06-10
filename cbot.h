#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <map>
#include <vector>

#include "cuser.h"
using namespace std;

class cBot
{
public:
    cBot(string filename);                  // open file to read
    void tailF();                           // equivalent "tail -f" bash command, notify if new user joins
    void displayFile(fstream &file);        // displays contents of a file
    void displayMap();                      // displays contents of a map

private:
    void addUser(vector<string> data);      // getting data from tailF() and saving to map
    int checkLenght(fstream &file);         // returns numbers of characters in file
    vector<string> splitString(string toSplit); // tails line to vector of strings

    string filename;                        // name of file to read
    map <string,cUser> usersList;           // map - contains nicknames, seen date, etc

};


