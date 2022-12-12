#! /usr/bin/env bash
echo "Run cmake rebuild (debug)..."
cd ../build/debug && rm -rf CMakeFiles/ && 
cmake -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . && ctest .. --output-on-failure && cmake --install . --config Debug && cd -
printf '\U1F44D Congrats! You are good to go\n'