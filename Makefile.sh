#!/bin/bash

g++ test/matrix_tests.cpp src/*.cpp -lm -o bin/matrix_tests

cd bin
./matrix_tests
