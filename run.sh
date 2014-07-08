#!/bin/bash  
source conf/irc.conf

date >> bot.log
./start-bot.sh  &> bot.log



