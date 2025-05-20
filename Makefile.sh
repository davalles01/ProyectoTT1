#!/bin/bash

g++ src/*.cpp -lm -o bin/EKF_GEOS3

cd bin
./EKF_GEOS3
