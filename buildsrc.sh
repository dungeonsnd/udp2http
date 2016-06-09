#!/bin/sh

cpprepos=../../cppmaven/cpprepos

cd src
g++ -Wall -g u2h_main.cpp -o u2h-server -I../include/ -I$cpprepos/curl-7.39.0/include -L$cpprepos/curl-7.39.0/lib/ -lcurl
mv u2h-server ../bin/
cd ../
