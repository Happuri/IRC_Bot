#include "cbot.h"

cBot::cBot(string &myNick, string &server, string &room) {
	cout << "\nStarting bot" << endl;
	string dir_ii = "ii-data/";
	string dir_u = "users/";
	this->myNick = myNick;
	this->server = server;
	this->room = room;
	this->filename = dir_ii + server + "/" + room + "/out";
	this->outFilename = dir_ii + server + "/" + room + "/in";
	this->filenameUsersList = dir_u + server + "-" + room + "-users.txt";
	this->separator = "|";

	string join = "echo /j '" + room + "' >> " + dir_ii + server + "/in";
	cout << "Executing command: " << join << endl;
	system(join.c_str());
	string createFile = "touch " + filenameUsersList;
	cout << "Executing command: " << createFile << endl;
	system(createFile.c_str()); // TODO nicer way to create file if not exist

	if (!load())
		cout << "Error with loads users list" << endl;
	printInfo();
}

void cBot::tailF() {
	string tmp = "", tmp2 = "", joined = "has joined", wordPing = "> PING";
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
		if (getNick(nickname) == this->myNick) {
			return;
		}
		string toSay = "Hello again, " + getNick(nickname);
		say(toSay);
		return;
	}
	cUser newUser(time, date);

	pair<map<string, cUser>::iterator, bool> ret;
	ret = this->usersList.insert(pair<string, cUser>(nickname, newUser));
	sayHello(nickname);

	save(nickname, time, date);
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
		cout << "   " << it->first << " => " << it->second.toString() << endl;
	cout << "------END MAP---------" << endl;
}

void cBot::say(string &what) {
	string command = "echo '" + what + "' >> " + outFilename;
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

	//string toSay = "Hello again, " + getNick(nickname);
	//say(toSay);

	return true;

}

bool cBot::load() {
	fstream file;
	file.open(filenameUsersList.c_str(), ios::in);
	string tmp;
	cout << "\nLoading users list form file: " << filenameUsersList << endl;
	while (!file.eof()) {
		getline(file, tmp);
		cout << tmp << endl;
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
	if (!file.good()) {
		cout << "Error with saving user to file. Can't open file: "
				<< filenameUsersList << endl;
		return false;
	}

	cout << "Saving to file: ";
	cout << nick << separator << date << separator << time << separator << "\n";

	file << nick << separator << date << separator << time << separator << "\n";
	file.close();
	return true;
}

cBot::~cBot() {
	cout
			<< "\n--------------------------------------------------------------------"
			<< endl;
}

void cBot::printInfo() {
	cout << "\n        ---------INFO---------" << endl;
	cout << "       Bot nickname: " << myNick << endl;
	cout << "           IRC room: " << room << endl;
	cout << "             Server: " << server << endl;
	cout << "Reading output from: " << filename << endl;
	cout << "          Saying to: " << outFilename << endl;
	cout << "              Users: " << filenameUsersList << endl;
	cout << "        -------END INFO-------" << endl;
}


