#! /usr/bin/env bash
echo "Run plain cmake build and install..."
mkdir ../build && cd ../build
cmake .. && make && make install && cd -
printf '\U1F44D Congrats! You are all set.\n'