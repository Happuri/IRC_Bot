#!/bin/bash  
source conf/irc.conf

date >> bot.log 
set -x
./start-ii.sh
nohup ./start-bot.sh  &> bot.log &



