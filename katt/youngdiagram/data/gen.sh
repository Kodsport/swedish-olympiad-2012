#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution joshua_precomp.cpp

compile gen.py

samplegroup
limits maxn=10
sample 1
sample 2

group group1 10
limits maxn=10
include_group sample
tc g1-1 gen n=1
tc g1-2 gen n=2
tc g1-3 gen n=3
tc g1-4 gen n=4
tc g1-5 gen n=5
tc g1-6 gen n=7
tc g1-7 gen n=8
tc g1-8 gen n=9

group group2 25
limits maxn=20
include_group group1
tc g2-1 gen n=11
tc g2-2 gen n=12
tc g2-3 gen n=13
tc g2-4 gen n=14
tc g2-5 gen n=15
tc g2-6 gen n=16
tc g2-7 gen n=17
tc g2-8 gen n=18
tc g2-9 gen n=19
tc g2-10 gen n=20

group group3 25
limits maxn=60
include_group group2
tc g3-1 gen n=25
tc g3-2 gen n=28
tc g3-3 gen n=30
tc g3-4 gen n=33
tc g3-5 gen n=35
tc g3-6 gen n=37
tc g3-7 gen n=39
tc g3-8 gen n=41
tc g3-9 gen n=49
tc g3-10 gen n=58
tc g3-11 gen n=59

group group4 40
limits maxn=100
include_group group3
tc g4-1 gen n=88
tc g4-2 gen n=87
tc g4-3 gen n=89
tc g4-4 gen n=98
tc g4-5 gen n=99
tc g4-6 gen n=100
