#!/bin/bash

################################################################################
# function : 4_bash
# description : 
#    prepare file (stru.dat) which is a list including all structure number you want
#
################################################################################
file="stru.dat"
ex_writestep="../writestep/a.out"

dir=`pwd`
#iend=`wc $file | cut -d' ' -f-10`
iend=`wc -l $file | cut -d' ' -f 1`
mkdir $dir/list_stru

echo total number of structures = $iend

#echo 74 > aaa.inp
#rm aaa.inp
 
for (( i=1; i<=$iend; i++ ))
do
   tail -$i $file > aaa
   num=`head -1 aaa` 
   echo $num > bbb
   echo $num 
   #tail -$i $file | head -1 | tee bbb  # "tee" command do both echo and make file
   $ex_writestep mdx.crd mdx.in.pdb < bbb > bbb.log
   mv out_step.pdb list_stru/$num.pdb
done

rm aaa bbb bbb.log

echo end
#ls $dir/list_stru
