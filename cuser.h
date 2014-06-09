#ifndef CUSER_H
#define CUSER_H

#include <fstream>

using namespace std;

class cUser
{
public:
    cUser(fstream &file);
    void Save();
    void Load();
private:
    int mSeenTime;

};

#endif // CUSER_H
