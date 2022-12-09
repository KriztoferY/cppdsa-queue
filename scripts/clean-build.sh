#! /usr/bin/env bash
echo "Clean local build, include, and lib directories..."
rm -rf ../build/
rm -rf ../bin/*
rm -rf ../lib/*
rm ../include/*.hpp
printf '\U1F44D Done!\n'
