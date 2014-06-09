#include <iostream>
#include <fstream>
#include <string>

#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <pthread.h>

#include <unistd.h>

#include "cuser.h"
#include "cbot.h"

using namespace std;


int main()
{
    string filename="example.txt";
    cBot testing(filename);
    testing.tailF();



    return 0;
}
