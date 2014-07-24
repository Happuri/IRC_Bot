#include "cuser.h"

cUser::cUser(long &timeDate) {
	ostringstream ss;
	this->timeDate = timeDate;
	ss << timeDate;
 	this->timeDateString = ss.str(); 
}

cUser::cUser(string &timeDateString) {
	this->timeDateString = timeDateString;

}


string cUser::toStringtimeDateString() {
	return timeDateString;

}
