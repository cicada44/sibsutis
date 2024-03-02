#!/bin/sh

g++ -Wall -Wextra -std=c++20 gps.cpp -o gps -lboost_system -lpthread -lboost_iostreams -lboost_serialization
