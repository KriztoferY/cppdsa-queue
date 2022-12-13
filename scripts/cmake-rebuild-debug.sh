#! /usr/bin/env bash
echo "Run cmake rebuild (debug)..."
cd ../build/debug && rm -rf CMakeFiles/ && 
if cmake -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . && ctest .. --output-on-failure && cmake --install . --config Debug && cd -
then echo '👍 Congrats! You are all set.'
else echo '👎 Oops! Something went wrong.'
fi