#! /usr/bin/env bash
echo "Run plain cmake build (release) and install..."
mkdir -p ../build/release && cd ../build/release
cmake -DCMAKE_BUILD_TYPE=Release ../.. && cmake --build . && ctest .. --output-on-failure && cmake --install . --config Release && cd -
echo '👍 Congrats! You are all set.'