#include "cuser.h"

cUser::cUser(string &mSeenFirstTime, string &mSeenFirstDate) {
	this->mSeenFirstTime = mSeenFirstTime;
	this->mSeenFirstDate = mSeenFirstDate;

}

string cUser::toString() {
	return mSeenFirstDate+"|"+mSeenFirstTime;

}
