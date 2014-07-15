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
// how to start:
// Debug/Bot nick server room
int main(int argc, char* argv[]) {
	string botname, server, room, room2;

	if (argc == 4) { // TODO some validation
		botname = argv[1];
		server = argv[2];
		room2 = argv[3];
	} else { // TODO get this data from conf file (?)
		cout << "No params, exit" << endl;
		return 0;

	}
	room="#"+room2;
	cout << "Botname: " << botname << endl;
	cout << " Server: " << server << endl;
	cout << "   Room: " << room << endl;

	cBot testing(botname, server, room);
	testing.tailF();

	//testing.sayHelloWorld();

	return 0;
}
