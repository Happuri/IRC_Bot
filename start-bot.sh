#!/bin/bash 

source conf/irc.conf 
set -x 

echo "Starting bot $NICK on $HOST server"


LOGFILE=bot$(date +"%Y-%m-%d-%H-%M-%S").log

nohup Debug/IRC_Bot $NICK $HOST $1 &> $LOGFILE &
