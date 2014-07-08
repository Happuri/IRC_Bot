#!/bin/bash 
source conf/irc.conf
set -x 
# start ii
nohup ii -f $HOSTNAME -n $NICK -i $DIR -s $HOST -p $PORT &


 

