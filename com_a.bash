#!/bin/bash

g++ lnPtoP.cpp -o lnPtoP.exe

./lnPtoP.exe ../p_cano/P_E_T300.dat Pc_T300.dat #$1:ln(P(E,300)), $2:output name
