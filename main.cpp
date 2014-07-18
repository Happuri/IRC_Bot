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
// ./start-bot.sh room
// TODO integrate with ii
int main(int argc, char* argv[]) {
	string botname, server, room, room2;

	if (argc == 4) {
		botname = argv[1];
		server = argv[2];
		room2 = argv[3];
	} else {
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
