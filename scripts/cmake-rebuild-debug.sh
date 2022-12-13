#! /usr/bin/env bash
echo "Run cmake rebuild (debug)..."
cd ../build/debug && rm -rf CMakeFiles/ && 
cmake -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . && ctest .. --output-on-failure && cmake --install . --config Debug && cd -
echo '👍 Congrats! You are all set.'