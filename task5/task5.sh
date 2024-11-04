#!/bin/bash

echo "Choose who to kill"
read STR
echo killing $STR
sleep 1
ps -u | grep $STR | awk '{print $2}'| xargs kill -kill
exit 0
