#! /usr/bin/env bash
echo "Run cmake rebuild (release)..."
cd ../build/release && rm -rf CMakeFiles/ && 
if cmake -DCMAKE_BUILD_TYPE=Release ../.. && cmake --build . && ctest .. --output-on-failure && cmake --install . --config Release && cd -
then echo '👍 Congrats! You are all set.'
else echo '👎 Oops! Something went wrong.'
fi