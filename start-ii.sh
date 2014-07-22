#!/bin/bash 
source conf/irc.conf
set -x 
# start ii
nohup ~/ii-dev/ii-1.6/ii -f $HOSTNAME -n $NICK -i $DIR -s $HOST -p $PORT &


 

