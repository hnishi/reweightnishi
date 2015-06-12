#!/bin/bash

################################################################################
# function : 6_bash
# description : 
#    prepare file (stru.dat) which is a list including all structure number you want
#
################################################################################
file="out_list.dat"
ex_writestep="../writestep/a.out"
outdir="list_stru_ref"


dir=`pwd`
#iend=`wc $file | cut -d' ' -f-10`
iend=`wc -l $file | cut -d' ' -f 1`
mkdir $dir/$outdir

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
   mv out_step.pdb $outdir/$num.pdb
done

rm aaa bbb bbb.log

echo end
ls $outdir
