#!/bin/bash

cat c1c2c3c4str.dat | awk '{print $1 "   " $2}' > aaa
paste aaa out_exPotEne.dat > file_3.dat

g++ pmfnishi.cpp inpnishi.cpp nlib.h -o pmfnishi.exe

rm aaa

