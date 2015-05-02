#!/bin/bash

rm exPotEne.exe
g++ exPotEne.cpp tranishi.cpp pdbnishi.cpp inpnishi.cpp -o exPotEne.exe

./exPotEne.exe inp_exPotEne.inp

cat c1c2c3c4str.dat | awk '{print $1 "   " $2}' > aaa
paste aaa out_exPotEne.dat > file_3.dat

rm aaa
