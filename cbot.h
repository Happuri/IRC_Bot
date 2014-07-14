#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <map>
#include <vector>
#include <stdio.h>      /* printf */
#include <stdlib.h>

#include "cuser.h"
using namespace std;

class cBot
{
public:
    cBot(string &myNick, string &filename, string &outFilename);                  // open file to read
    ~cBot();								// destructor
    void tailF();                           // equivalent "tail -f" bash command, notify if new user joins
    void displayFile(fstream &file);        // displays contents of a file
    void displayMap();                      // displays contents of a map
    void say(string &what);
    void sayHello(string &username);
    void sayHelloWorld();
    void PingPong();
    bool load();							// loading users from file to map
    bool save();							// saving map with users to file
    bool save(string &nick, string &time, string &date); // saving user to file

private:
    void addUser(vector<string> data);      // getting data from tailF() and saving to map
    int checkLenght(fstream &file);         // returns numbers of characters in file
    string getNick(string &all);
    vector<string> splitString(string &toSplit, string delimiter); // tails line to vector of strings
    bool parse(string line);				// parsing

    string separator;
    string myNick;
    string outFilename;
    string filename;                        // name of file to read
    string filenameUsersList; 				// name of file with users
    map <string,cUser> usersList;           // map - contains nicknames, seen date, etc


};


