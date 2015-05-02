#!/bin/bash

g++ pmfnishi.cpp inpnishi.cpp nlib.h -o pmfnishi.exe

./pmfnishi.exe inp_pmf.inp > res3.log

paste file_3.dat out_prob.dat > prob.dat


