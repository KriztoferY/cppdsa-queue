#! /usr/bin/env bash
echo "Run cmake rebuild..."
cd ../build/ && rm -rf CMakeFiles/ && 
cmake .. && make && make install && cd -
printf '\U1F44D Congrats! You are good to go\n'