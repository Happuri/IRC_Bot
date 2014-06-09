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
                    if(found!=string::npos) {
                        cout << "New user joined!" << endl;
                        // TODO: add user to map if doesn't exist
                    }


                }
            }
        }

        cout << "\nsleeping\n"<< endl;
        sleep(5);
        file.close();

    }
    while(true);


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
