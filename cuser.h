#ifndef CUSER_H
#define CUSER_H

#include <fstream>

using namespace std;

class cUser
{
public:
    cUser(string &mSeenTime, string &mSeenDate);
    string toString();
private:
    string mSeenTime;
    string mSeenDate;
};

#endif // CUSER_H
