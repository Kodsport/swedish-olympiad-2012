#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution uppg3.cpp


samplegroup
sample 01
sample 02
sample 03

group group1 40
tc_manual g1-1
tc_manual g1-2
tc_manual g1-3

group group2 60
include_group group1
include_group sample
tc_manual g2-1
tc_manual g2-2
tc_manual g2-3
