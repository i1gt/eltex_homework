#!/bin/bash

MODULE_NAME="task1"
LOG_FILE="/var/log/task1.log"

lsmod | grep "$MODULE_NAME"

echo "Log before removal:"
cat "$LOG_FILE"

echo "removeing module"
sudo rmmod "$MODULE_NAME"

echo "Log after removal:"
cat "$LOG_FILE"
