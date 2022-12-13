#! /usr/bin/env bash
echo "Run cmake rebuild (release)..."
cd ../build/release && rm -rf CMakeFiles/ && 
cmake -DCMAKE_BUILD_TYPE=Release ../.. && cmake --build . && ctest .. --output-on-failure && cmake --install . --config Release && cd -
echo '👍 Congrats! You are all set.'