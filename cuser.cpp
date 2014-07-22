#include "cuser.h"

cUser::cUser(string &mSeenFirstTime, string &mSeenFirstDate) {
	this->mSeenFirstTime = mSeenFirstTime;
	this->mSeenFirstDate = mSeenFirstDate;

}

cUser::cUser(long &timeDate) {
	ostringstream ss;
	this->timeDate = timeDate;
	ss << timeDate;
 	this->timeDateString = ss.str(); 
}

cUser::cUser(string &timeDateString) {
	this->timeDateString = timeDateString;

}

string cUser::toString() {
	return mSeenFirstDate+"|"+mSeenFirstTime;

}

string cUser::toStringtimeDateString() {
	return timeDateString;

}
