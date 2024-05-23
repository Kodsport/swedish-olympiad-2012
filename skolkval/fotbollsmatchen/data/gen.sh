#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution uppg6.cpp


samplegroup
limits maxn=100
sample 1
sample 2
sample 3

group group1 20
limits maxn=4
tc_manual g1-1
tc_manual g1-2
tc_manual g1-3

group group2 20
limits maxn=9
include_group group1
tc_manual g2-1
tc_manual g2-2
tc_manual g2-3

group group3 60
limits maxn=100
include_group group2
include_group sample
tc_manual g3-1
tc_manual g3-2
tc_manual g3-3
