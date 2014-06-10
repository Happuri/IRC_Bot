#include "cbot.h"

cBot::cBot(string filename)
{
    this->filename=filename;
}

void cBot::tailF()
{
    string tmp="", tmp2="", joined="has joined";
    size_t found;
    fstream file;
    int tmpLen=0;

    do {
        cout << "run\n"<< endl;
        file.open(this->filename.c_str(), ios::in);

        if(checkLenght(file)!=tmpLen) {
            file.seekg(tmpLen, file.beg);

            tmpLen=checkLenght(file);
            cout << tmpLen << endl;

            while (!file.eof()) {
                getline(file,tmp);
                //file >> tmp;
                if(tmp!=tmp2) {
                    cout << tmp << " ";
                    tmp2 = tmp;
                    found = tmp.find(joined);

                    // if new user has joined adds him to map
                    if(found!=string::npos) {
                        cout << "---New user joined!---" << endl;
                        addUser(splitString(tmp));
                    }
                }
            }
        }

        cout << "\nsleeping\n"<< endl;
        sleep(5);
        file.close();

    } while(true);
}


int cBot::checkLenght(fstream &file)
{
    int tmpPosition=file.tellg();
    file.seekg (0, file.end); // go to end file
    int length = file.tellg(); // read position
    //ile.seekg (0, file.beg); // go back to the beginn
    file.seekg (tmpPosition, file.beg);
    return length;
}


void cBot::displayFile(fstream &file)
{
    string tmp;
    while(!file.eof()) {
        getline(file,tmp);
        cout << tmp << endl;
    }
}


void cBot::addUser(vector<string> data)
{
    /*cout << "-----------------" << endl;
    for (string tmp : data)
        cout << tmp << endl;
    cout << "-----------------" << endl;*/

    // reading data from vector
    string nickname, date, time;
    nickname=data.at(3);
    date=data.at(0);
    time=data.at(1);

    /*
    cout << "-----------------" << endl ;
    cout << "--nickname: " << nickname << "--date: " << date << "--time: " << time << endl;
    cout << "-----------------" << endl;*/

    cUser newUser(time,date);

    pair<map<string,cUser>::iterator,bool> ret;
    ret = this->usersList.insert ( pair<string,cUser>(nickname,newUser));
    displayMap();
}

vector<string> cBot::splitString(string toSplit)
{
    string delimiter = " ",token;
    size_t pos = 0;
    vector <string> data;
    //cout << "-----------------" << endl;

    while ((pos = toSplit.find(delimiter)) != string::npos) {
        token = toSplit.substr(0, pos);
        //cout << token << "; " << i << endl;
        toSplit.erase(0, pos + delimiter.length());
        data.push_back(token);

    }
    //std::cout << toSplit << std::endl;
    //cout << "-----------------" << endl;
    return data;

}

void cBot::displayMap()
{
    cout << "---DISPLAYING MAP!!---" << endl;
    map<string,cUser>::iterator it = this->usersList.begin();
    for (it=this->usersList.begin(); it!=this->usersList.end(); ++it)
         cout << it->first << endl; //" => " << it->second << '\n';
    cout << "-----------------" << endl;
}
