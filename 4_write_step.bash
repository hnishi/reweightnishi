#!/bin/bash

mkdir list_stru

echo 74 > aaa.inp
../writestep/a.out mdx.crd mdx.in.pdb < aaa.inp > aaa.log
mv out_step.pdb list_stru/74.pdb

rm aaa.inp


74
76
88
97
101
103
104
105
106
107
110
111
119
125
128
135
137
138
143
150

