#!/bin/bash  
source conf/irc.conf

date >> bot.log
nohup ./start-bot.sh  &> bot.log &



