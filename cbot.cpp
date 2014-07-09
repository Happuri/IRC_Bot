#include "cbot.h"

cBot::cBot(string &myNick, string &filename, string &outFilename) {
	this->myNick = myNick;
	this->filename = filename;
	this->outFilename = outFilename;
	//this->usersList.insert(pair<string, cUser>(myNick, NULL));
}

void cBot::tailF() {
	string tmp = "", tmp2 = "", joined = "has joined";
	size_t found;
	fstream file;
	int tmpLen = 0;

	do {
		//cout << "run\n" << endl;
		file.open(this->filename.c_str(), ios::in);

		if (checkLenght(file) != tmpLen) {
			file.seekg(tmpLen, file.beg);

			tmpLen = checkLenght(file);
			cout << tmpLen << endl;

			while (!file.eof()) {
				getline(file, tmp);
				//file >> tmp;
				if (tmp != tmp2) {
					cout << tmp << " ";
					tmp2 = tmp;
					found = tmp.find(joined);

					// if new user has joined adds him to map
					if (found != string::npos) {
						cout << "---New user joined!---" << endl;
						addUser(splitString(tmp));
					}
				}
			}
		}
		//cout << "\nsleeping\n" << endl;
		sleep(5);
		file.close();

	} while (true);
}

int cBot::checkLenght(fstream &file) {
	int tmpPosition = file.tellg();
	file.seekg(0, file.end); // go to end file
	int length = file.tellg(); // read position
	//ile.seekg (0, file.beg); // go back to the beginn
	file.seekg(tmpPosition, file.beg);
	return length;
}

void cBot::displayFile(fstream &file) {
	string tmp;
	while (!file.eof()) {
		getline(file, tmp);
		cout << tmp << endl;
	}
}

void cBot::addUser(vector<string> data) {
	// reading data from vector
	string nickname, date, time;
	nickname = data.at(3);
	date = data.at(0);
	time = data.at(1);

	cUser newUser(time, date);

	pair<map<string, cUser>::iterator, bool> ret;
	ret = this->usersList.insert(pair<string, cUser>(nickname, newUser));
	sayHello(nickname);
	displayMap();
}

vector<string> cBot::splitString(string &toSplit) {
	string delimiter = " ", token;
	size_t pos = 0;
	vector<string> data;

	while ((pos = toSplit.find(delimiter)) != string::npos) {
		token = toSplit.substr(0, pos);
		toSplit.erase(0, pos + delimiter.length());
		data.push_back(token);
	}
	return data;

}

void cBot::displayMap() {
	cout << "---DISPLAYING MAP!!---" << endl;
	map<string, cUser>::iterator it = this->usersList.begin();
	for (it = this->usersList.begin(); it != this->usersList.end(); ++it)
		cout << it->first << endl;
	//cout << it->first << " => " << it->second << endl;
	cout << "-----------------" << endl;
}

void cBot::say(string &what) {
	string command = "echo " + what + ">> " + outFilename;
	system(command.c_str()); // TODO
}

void cBot::sayHello(string &username) {
	string nick = getNick(username);
	if (nick == this->myNick)
		return;
	string toSay = "Hello " + nick;
	say(toSay);

}

string cBot::getNick(string &all) {
	size_t pos = all.find("(");
	return all.substr(0, pos);
}
