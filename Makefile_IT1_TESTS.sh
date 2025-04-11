#!/bin/bash

g++ test/It1_tests.cpp src/*.cpp -lm -o bin/It1_tests

cd bin
./It1_tests
