#include "cbot.h"

cBot::cBot(string &myNick, string &server, string &room) {
	cout << "\nStarting bot" << endl;
	string dir_ii = "ii-data/";
	string dir_u = "users/";
	string dir_data = "data/";

	this->myNick = myNick;
	this->server = server;
	this->room = room;
	this->filename = dir_ii + server + "/" + room + "/out";
	this->outFilename = dir_ii + server + "/" + room + "/in";
	this->filenameUsersList = dir_u + server + "-" + room + "-users.txt";
	this->fileDataInfo = dir_data + server + "/" + room + "/data.txt";
	this->separator = "|";
	this->nowTime = nowTime;
	this->timeOfNotHelloBreak = timeOfNotHelloBreak;

	string join = "echo /j '" + room + "' >> " + dir_ii + server + "/in";
	cout << DBG << "Joining room. Executing command: " << join << endl;
	system(join.c_str());
	cout << DBG << "Sleeping(10)" << endl;
	sleep(10);
	string createFile = "touch " + filenameUsersList;
	cout << DBG << "Creating file with users list. Executing command: " << createFile << endl;
	system(createFile.c_str()); // TODO nicer way to create file if not exist
	string createFileOfCustomData = "touch " + fileDataInfo;
	cout << DBG << "Creating file with Custom Data. Executing command: " << createFile << endl;
	system(createFileOfCustomData.c_str()); // TODO nicer way to create file if not exist

	if (!load())
		cout << __FUNCTION__ << ": Error with loads users list" << endl;
	if (!loadCustomData())
		cout << __FUNCTION__ << ": Error with loads custom data" << endl;
	printInfo();
}

void cBot::tailF() {
	string tmp = "", tmp2 = "", joined = "has joined", wordPing = "> PING";
	size_t found;
	fstream file;
	int tmpLen = 0;

	do { // infinite loop
		 // open out file
		file.open(this->filename.c_str(), ios::in);
		if (!file.good()) {
			cout << DBG << " Can't open file: " << filename << endl;
		} else {
			if (checkLenght(file) != tmpLen) {
				file.seekg(tmpLen, file.beg);

				tmpLen = checkLenght(file);
				cout << DBG << ": tmpLen: " << tmpLen << endl;

				while (!file.eof()) {
					getline(file, tmp);
					//file >> tmp;
					if (tmp != tmp2) {
						cout << DBG << tmp << " ";
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
		}
		//cout << "\nsleeping\n" << endl;
		cout << DBG << "Sleeping(5): " << tmpLen << endl;
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
	
	time(&nowTime);		//get system time
	timeOfNotHelloBreak = 3600 * 24 * 7;
	
	// new user really joined?
	if (data.at(2) != "-!-") {
		return;
	}

	// reading data from vector
	string &nickname = data.at(3);
	string &date = data.at(0);
	string &time = data.at(1);

	// if element exist in map
	map<string, cUser>::iterator it = this->usersList.find(nickname);
	if (it != usersList.end()) {
		
		// not hello itself
		if (getNick(nickname) == this->myNick) {
			return;
		}
		
		string timeOfUserString = it->second.toStringtimeDateString();		//Get time of user joins and convert it to long
		long timeOfUser = atol(timeOfUserString.c_str());

		if ((nowTime - timeOfUser) > timeOfNotHelloBreak){
			// says hello again and returns
			string toSay = "Hello again, " + getNick(nickname);
			say(toSay);
			
			it->second = nowTime;			// Replace time
			save();							// Save all map to users.txt
		}
		return;
	}

	// if not exist - create them and save to file
	cUser newUser(nowTime);

	pair<map<string, cUser>::iterator, bool> ret;
	ret = this->usersList.insert(pair<string, cUser>(nickname, newUser));
	sayHello(nickname);
	cout << DBG << nowTime << endl;
	save(nickname, nowTime);
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
		cout << "   " << it->first << " => " << it->second.toStringtimeDateString() << endl;
	cout << "------END MAP---------" << endl;
}

void cBot::displayMapOfCustomData() {
	cout << "---DISPLAYING MAP OF CUSTOM DATA!!---" << endl;
	map<string, string>::iterator it = this->customData.begin();
	for (it = this->customData.begin(); it != this->customData.end(); ++it)
		cout << "   " << it->first << " => " << it->second << endl;
	cout << "------END MAP OF CUSTOM DATA---------" << endl;
}

void cBot::say(string &what) {
	string command = "echo '" + what + "' >> " + outFilename;
	system(command.c_str()); // TODO
}

void cBot::sayHello(string &username) {
	map<string, string>::iterator it = this->customData.find("helloText");
	string textHello = it->second;
	string nick = getNick(username);
	if (nick == this->myNick)
		return;
	string toSay = "Hello " + nick + " " + textHello;
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
	// mempobot(mempobot@i.love.debian.org)|xxxxxxxxxxxx|

	if (line.empty())
		return false;

	vector<string> toSave = splitString(line, separator);

	string &nickname = toSave.at(0);
	string &nowTimeString = toSave.at(1);
	
	cUser newUser(nowTimeString);
	cout << "nickname: " << nickname << endl;
	cout << "nowTimeString: " << nowTimeString << endl;
	pair<map<string, cUser>::iterator, bool> ret;
	ret = this->usersList.insert(pair<string, cUser>(nickname, newUser));

	return true;
}

bool cBot::parseCustomData(string line) {
	// to parse:
	// mempobot(mempobot@i.love.debian.org)|xxxxxxxxxxxx|

	if (line.empty())
		return false;

	vector<string> toSave = splitString(line, separator);

	string &nameOfCustomData = toSave.at(0);
	string &contentOfCustomData = toSave.at(1);
	
	cout << "nameOfCustomData: " << nameOfCustomData << endl;
	cout << "contentOfCustomData: " << contentOfCustomData << endl;
	pair<map<string, string>::iterator, bool> ret;
	ret = this->customData.insert(pair<string, string>(nameOfCustomData, contentOfCustomData));

	return true;
}

bool cBot::load() {
	fstream file;
	file.open(filenameUsersList.c_str(), ios::in);
	if (!file.good()) {
		cout << DBG << "Can't open file: " << filename << endl;
		return false;
	}

	string tmp;
	cout << "\n " << DBG << " Loading users list form file: " << filenameUsersList << endl;
	while (!file.eof()) {
		getline(file, tmp);
		cout << DBG << tmp << endl;
		parse(tmp);
	}
	displayMap();

	file.close();
	return true;
}

bool cBot::loadCustomData() {
	fstream file;
	file.open(fileDataInfo.c_str(), ios::in);
	if (!file.good()) {
		cout << DBG << "Can't open file: " << filename << endl;
		return false;
	}

	string tmp;
	cout << "\n " << DBG << " Loading custom data form file: " << fileDataInfo << endl;
	while (!file.eof()) {
		getline(file, tmp);
		cout << DBG << tmp << endl;
		parseCustomData(tmp);
	}
	displayMapOfCustomData();

	file.close();
	return true;
}

bool cBot::save() {
	fstream file;
	file.open(filenameUsersList.c_str(), ios::out | ios::trunc);

	map<string, cUser>::iterator it = this->usersList.begin();
	for (it = this->usersList.begin(); it != this->usersList.end(); ++it)
		file << it->first << separator << it->second.toStringtimeDateString() << separator << "\n";
	file.close();
	return true;
}

bool cBot::save(string &nick, string &time, string &date) {
	fstream file;
	file.open(filenameUsersList.c_str(), ios::out | ios::app);
	if (!file.good()) {
		cout << DBG << "Error with saving user to file. Can't open file: " << filenameUsersList << endl;
		return false;
	}

	cout << DBG << "Saving to file: ";
	cout << nick << separator << date << separator << time << separator << "\n";

	file << nick << separator << date << separator << time << separator << "\n";
	file.close();
	return true;
}

bool cBot::save(string &nick, long &timeDate) {
	fstream file;
	file.open(filenameUsersList.c_str(), ios::out | ios::app);
	if (!file.good()) {
		cout << DBG << "Error with saving user to file. Can't open file: " << filenameUsersList << endl;
		return false;
	}

	cout << DBG << "Saving to file: ";
	cout << nick << separator << timeDate << separator << "\n";

	file << nick << separator << timeDate << separator << "\n";
	file.close();
	return true;
}

cBot::~cBot() {
	cout << "\n--------------------------------------------------------------------" << endl;
}

void cBot::printInfo() {
	cout << "\n        ---------INFO---------" << endl;
	cout << "       Bot nickname: " << myNick << endl;
	cout << "           IRC room: " << room << endl;
	cout << "             Server: " << server << endl;
	cout << "Reading output from: " << filename << endl;
	cout << "          Saying to: " << outFilename << endl;
	cout << "              Users: " << filenameUsersList << endl;
	cout << "               Data: " << fileDataInfo << endl;
	cout << "        -------END INFO-------" << endl;
}

