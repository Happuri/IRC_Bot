#!/bin/bash 

source conf/irc.conf 
set -x 

echo "/j $CHAN" >> $SERV_PATH/in

#echo $FROM 
#echo $TO

#date >> $LOGFILE
Debug/IRC_Bot $NICK $FROM $TO #&> $LOGFILE
