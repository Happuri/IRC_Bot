#ifndef CUSER_H
#define CUSER_H

#include <fstream>
#include <sstream>

using namespace std;

class cUser
{
public:
    cUser(string &mSeenTime, string &mSeenDate);
    cUser(long &timeDate);
    cUser(string &timeDateString);
    string toString();
    string toStringtimeDateString();
private:
    string mSeenTime;
    string mSeenDate;
	string timeDateString;
	long timeDate;
};

#endif // CUSER_H
