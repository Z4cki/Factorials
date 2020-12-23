#!/bin/bash
mkdir -p bin && g++ src/factorial.cpp -o bin/factorial -pthread -lgmp -lgmpxx -std=c++17