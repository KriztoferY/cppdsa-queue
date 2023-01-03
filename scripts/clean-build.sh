#! /usr/bin/env bash
echo "Clean local build, bin, include, and lib directories..."
rm -rf ../build/
rm -rf ../bin/*
rm -rf ../lib/*
rm -rf ../include/*
# rm ../include/*.hpp
echo '👍 Done!'
