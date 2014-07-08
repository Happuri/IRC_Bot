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

int main(int argc, char* argv[]) {
	string botname, from, to;

	if (argc == 4) {
		botname = argv[1];
		from = argv[2];
		to = argv[3];
	} else {
		cout << "No params, exit" << endl;
		return 0;

	}
	cout << "Botname: " << botname << endl;
	cout << "From: " << from << endl;
	cout << "To: " << to << endl;

	cBot testing(botname, from, to);
	testing.tailF();

	return 0;
}
