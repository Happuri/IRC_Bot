#!/bin/bash 

source conf/irc.conf 
set -x 

#echo "/j $CHAN" >> $SERV_PATH/in

#echo $FROM 
#echo $TO

LOGFILE=bot$(date +"%Y-%m-%d-%H-%M-%S").log

nohup Debug/IRC_Bot $1 $2 $3 &> $LOGFILE &
