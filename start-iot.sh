#!/bin/sh

file_name=./.lck

if [ -e "$file_name" ]
then
    echo "There is another process of IOT-Raspberry running. Please close that before starting. If there are no other IOT-Raspberry process running, please delete the .lck file and start again"
exit 1
fi

echo "Starting the IoT-Raspberry"

#cd ./bin
export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
./iot >> iot.log &
pid=$!

echo $pid >.pid

echo "Started the IoT-Raspberry. Running with pid : $pid"
