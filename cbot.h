#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <curl/curl.h>

#include "cuser.h"

#define DBG __FUNCTION__<<":"<< __LINE__<<"\t"

using namespace std;

class cBot
{
public:
    cBot(string &myNick, string &filename, string &outFilename);
    ~cBot();								// destructor
    void tailF();                           // equivalent "tail -f" bash command, notify if new user joins
    void displayFile(fstream &file);        // displays contents of a file
    void displayMap();                      // displays contents of a map
    void displayMapOfCustomData();
    void say(string &what);					// says in irc
    void sayHello(string &username);		// says "hello", when user joins first time
    void sayHelloWorld();					// TODO to tests
    void PingPong();						// to playing ping pong
    void NumberOfUsers();					// displays number of users
    void MoneroPrice();                     // displays price of monero
    void calcMonero(vector<string> data);   // calc price of provide value of monero
    void getMoneroPrice();
    bool load();							// loading users from file to map
    bool save();							// remove content of filenameUsersList and save actual map
    bool save(string &nick, string &time, string &date); // saving single user to file
    bool save(string &nick, long &timeDate);
    bool loadCustomData();					// Loading and parsing custom data
    void printInfo();						// printing informations about bot
    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

private:
    void addUser(vector<string> data);      // getting data from tailF() and saving to map
    int checkLenght(fstream &file);         // returns numbers of characters in file
    string getNick(string &all);			// returns plain nick
    vector<string> splitString(string &toSplit, string delimiter); // tails line to vector of strings
    bool parse(string line);				// parsing
    bool parseCustomData(string line);
    double string2double(const char *strNr);     //convert string to double


    string separator;						// | used in users list
    string myNick;							// bot's nickname
    string server;							// server irc
    string room;							// #room in irc
    string outFilename;						// saying to this file
    string filename;                        // name of file to read
    string filenameUsersList; 				// name of file with users
    string fileDataInfo; 					// TODO
    string priceOfMonero;                   // Price of monero
    map <string,cUser> usersList;           // map - contains nicknames, seen date, etc
    map <string,string> customData;			// map contains all provided data
    
    long nowTime;							// Timer
    int timeOfNotHelloBreak;				//
    int timeOfMoneroPrice;                  // Time of current file with price of monero
};


