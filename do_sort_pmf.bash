#!/bin/bash


grep -v "1000\.000"  $1 | grep ... | sort -n -k 3
#grep -v "100\.000"  pcanishi/out_pmf.dat | grep ... | sort -n -k 3
