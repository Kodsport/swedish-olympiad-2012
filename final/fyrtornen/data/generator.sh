#!/usr/bin/env bash

. ../../../testdata_tools/gen.sh

use_solution joshua.cpp

compile gen.py

samplegroup
limits maxm=20
sample sample01
sample sample02

group group1 10
limits maxm=2000
include_group sample
tc_manual ../manual_data/fyrtornen1.in
tc_manual ../manual_data/fyrtornen2.in
tc g1-1 gen n=1000 m=2000 k=10 mode=rand
tc g1-2 gen n=10000 m=2000 k=100 mode=rand
tc g1-3 gen n=300000 m=2000 k=1000 mode=rand
tc g1-4 gen n=100 m=2000 k=2000 mode=rand
tc g1-5 gen n=10000 m=2000 k=1 mode=stairs
tc g1-6 gen n=10000 m=2000 k=1 mode=line
tc g1-7 gen n=300000 m=2000 k=20 mode=midsize

group group2 30
limits maxm=30000
include_group group1
tc_manual ../manual_data/fyrtornen3.in
tc g2-1 gen n=1000 m=30000 k=3 mode=rand
tc g2-2 gen n=10000 m=30000 k=100 mode=rand
tc g2-3 gen n=300000 m=30000 k=1000 mode=rand
tc g2-4 gen n=300000 m=30000 k=1 mode=stairs
tc g2-5 gen n=300000 m=30000 k=1 mode=line
tc g2-6 gen n=300000 m=30000 k=50 mode=midsize

group group3 60
limits maxm=500000
include_group group2
tc_manual ../manual_data/fyrtornen4.in
tc_manual ../manual_data/fyrtornen5.in
tc g3-1 gen n=1000 m=500000 k=3 mode=rand
tc g3-2 gen n=10000 m=500000 k=5 mode=rand
tc g3-3 gen n=300000 m=500000 k=4 mode=rand
tc g3-4 gen n=300000 m=500000 k=1 mode=stairs
tc g3-5 gen n=300000 m=300000 k=1 mode=line
tc g3-6 gen n=300000 m=500000 k=100 mode=midsize
