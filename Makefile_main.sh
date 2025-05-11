#!/bin/bash

g++ test/main.cpp src/*.cpp -lm -o bin/main

cd bin
./main
