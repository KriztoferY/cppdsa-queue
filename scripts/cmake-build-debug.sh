#! /usr/bin/env bash
echo "Run plain cmake build (debug) and install..."
mkdir -p ../build/debug && cd ../build/debug
if cmake -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . && ctest .. --output-on-failure && cmake --install . --config Debug && cd -
then echo '👍 Congrats! You are all set.'
else echo '👎 Oops! Something went wrong.'
fi