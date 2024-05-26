#!/bin/bash

SRC=$1
OUT=${2:-a.out}

g++ $SRC `pkg-config python3-embed --libs --cflags` -o $OUT