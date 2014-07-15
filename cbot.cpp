#include "cbot.h"

cBot::cBot(string &myNick, string &filename, string &outFilename) {
	this->myNick = myNick;
	this->filename = filename;
	this->outFilename = outFilename;
	this->filenameUsersList = "users.txt";
	this->separator = "|";
	if (!load())
		cout << "Some error with loads users list" << endl;
}

void cBot::tailF() {
	string tmp = "", tmp2 = "", joined = "has joined", wordPing = "PING";
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
						addUser(splitString(tmp, " "));
					}

					found = tmp.find(wordPing);
					if (found != string::npos) {
						cout << "---PING---" << endl;
						PingPong();

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

	string &nickname = data.at(3);
	string &date = data.at(0);
	string &time = data.at(1);

	// if element exist
	map<string, cUser>::iterator it = this->usersList.find(nickname);
	if (it != usersList.end()) {
		// says hello again and returns
		string toSay = "Hello again, " + getNick(nickname);
		say(toSay);
		return;
	}
	cUser newUser(time, date);

	pair<map<string, cUser>::iterator, bool> ret;
	ret = this->usersList.insert(pair<string, cUser>(nickname, newUser));
	sayHello(nickname);

	save(nickname,time,date);
	displayMap();
}

vector<string> cBot::splitString(string &toSplit, string delimiter) {
	string token;
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
		cout << it->first << " => " << it->second.toString() << endl;
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

void cBot::sayHelloWorld() {
	string toSay = "Hello channel!";
	say(toSay);
}

void cBot::PingPong() {
	string wordPong = "PONG";
	say(wordPong);

}

bool cBot::parse(string line) {
	// to parse:
	// mempobot(mempobot@i.love.debian.org)|2014-06-09|01:36|

	if (line.empty())
		return false;

	vector<string> toSave = splitString(line, separator);

	string &nickname = toSave.at(0);
	string &date = toSave.at(1);
	string &time = toSave.at(2);

	cUser newUser(time, date);

	pair<map<string, cUser>::iterator, bool> ret;
	ret = this->usersList.insert(pair<string, cUser>(nickname, newUser));


	string toSay = "Hello again, " + getNick(nickname);
	say(toSay);

	return true;

}

bool cBot::load() {
	fstream file;
	file.open(filenameUsersList.c_str(), ios::in);
	string tmp;
	cout << "Loading users list form file: " << filenameUsersList << endl;
	while (!file.eof()) {
		getline(file, tmp); cout << tmp << endl;
		parse(tmp);
	}
	displayMap();

	file.close();
	return true;
}

bool cBot::save() {
	// open file
	fstream file;
	file.open(filenameUsersList.c_str(), ios::out | ios::trunc);

	map<string, cUser>::iterator it = this->usersList.begin();
	for (it = this->usersList.begin(); it != this->usersList.end(); ++it)
		file << it->first << separator << it->second.toString() << separator
				<< "\n";
	file.close();
	return true;
}

bool cBot::save(string &nick, string &time, string &date) {
	fstream file;
	file.open(filenameUsersList.c_str(), ios::out | ios::app);
	if(!file.good()) {
		cout << "Error with saving user to file. Can't open file: " << filenameUsersList << endl;
		return false;
	}

	cout << "Saving to file: ";
	cout << nick << separator << date << separator << time << separator << "\n";

	file << nick << separator << date << separator << time << separator << "\n";
	file.close();
	return true;
}

cBot::~cBot() {
	cout << "--------------------------------------------------------------------" << endl;
}

