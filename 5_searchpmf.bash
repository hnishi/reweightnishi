#!/bin/bash

# discription of searchpmf.cpp
#    search structures which are included in specified bin (PCA coordinates)
#

rm searchpmf.exe
g++ searchpmf.cpp inpnishi.cpp nlib.h -o searchpmf.exe

./searchpmf.exe inp_srcpmf.inp > res5.log

paste file_3.dat out_prob.dat > prob.dat


