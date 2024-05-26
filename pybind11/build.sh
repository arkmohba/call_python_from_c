#!/bin/bash

# SRC=$1
# OUT=${2:-a.out}

# g++ $SRC `pkg-config python3-embed --libs --cflags` -o $OUT
# g++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` ex1_basic_call.cpp -o example`python3-config --extension-suffix`
g++ -O3 -Wall -std=c++17 ex2_embedding_call_statement.cpp `python3 -m pybind11 --includes` `pkg-config python3-embed --cflags --libs`
g++ -O3 -Wall -std=c++17 ex2_embedding_call_statement.cpp `pkg-config python3-embed pybind11 --cflags --libs`

g++ -O3 -Wall -std=c++17 ex3_call.cpp `python3 -m pybind11 --includes` `pkg-config python3-embed --cflags --libs`

g++ -O3 -Wall -std=c++17 ex4_call_class_method.cpp `python3 -m pybind11 --includes` `pkg-config python3-embed --cflags --libs`
