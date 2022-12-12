#! /usr/bin/env bash
echo "Run cmake rebuild (release)..."
cd ../build/release && rm -rf CMakeFiles/ && 
cmake -DCMAKE_BUILD_TYPE=Release ../.. && cmake --build . && cmake --install . --config Release && cd -
printf '\U1F44D Congrats! You are good to go\n'