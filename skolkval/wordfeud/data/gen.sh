#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution uppg2.cpp


samplegroup
sample 01
sample 02
sample 03

group group1 50
limits disallow_mul=1
tc_manual g1-1
tc_manual g1-2
tc_manual g1-3

group group2 50
include_group group1
include_group sample
tc_manual s01
tc_manual s02
tc_manual s03
