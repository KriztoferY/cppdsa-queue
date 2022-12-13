#! /usr/bin/env bash
echo "Run plain cmake build (debug) and install..."
mkdir -p ../build/debug && cd ../build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . && ctest .. --output-on-failure && cmake --install . --config Debug && cd -
echo '👍 Congrats! You are all set.'