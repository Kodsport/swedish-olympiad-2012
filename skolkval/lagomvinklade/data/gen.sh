#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution uppg1.cpp

compile echo.py

samplegroup
limits maxn=100
sample sample1
sample sample2

group group1 30
limits maxn=7
tc g1-1 echo 1
tc g1-2 echo 2
tc g1-3 echo 3
tc g1-4 echo 4
tc g1-5 echo 5
tc g1-6 echo 6
tc g1-7 echo 7


group group2 70
limits maxn=100
include_group group1
include_group sample
tc_manual secret1
tc_manual secret2
tc_manual secret3
