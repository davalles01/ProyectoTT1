#!/bin/bash

g++ test/It2_tests.cpp src/*.cpp -lm -o bin/It2_tests

cd bin
./It2_tests
