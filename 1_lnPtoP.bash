#!/bin/bash

g++ lnPtoP.cpp -o lnPtoP.exe  

./lnPtoP.exe P_E_T300.dat Pc_T300.dat > res1.log #$1:ln(P(E,300)), $2:output name
