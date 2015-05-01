#!/bin/bash

rm exPotEne.exe
g++ exPotEne.cpp tranishi.cpp pdbnishi.cpp inpnishi.cpp -o exPotEne.exe

./exPotEne.exe inp_exPotEne.inp

