#!/bin/bash

cmake -DBUILD_TESTS=1 -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -S . -B build
cmake --build build
