#!/bin/bash

SRC_FILES=$(find src -name '*.cpp' ! -name 'EKF_GEOS3.cpp')

g++ test/tests.cpp $SRC_FILES -lm -o bin/tests

cd bin
./tests
