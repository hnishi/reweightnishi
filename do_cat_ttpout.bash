#!/bin/bash

num=64
#dir=/work1/hnishi/4thTrial/ama2/md/md23
dir=$(pwd)
nline=$(wc -l no1/ttp_v_mcmd.out|awk '{print $1}')
let "nline=$nline-1"

echo $nline
rm all_ttp_v_mcmd.out

for((i=1;i<=$num;i++))
do
  head -$nline $dir/no$i/ttp_v_mcmd.out >> all_ttp_v_mcmd.out
done

