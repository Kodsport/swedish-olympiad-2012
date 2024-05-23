#!/bin/bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution uppg5.java

samplegroup
sample 1
sample 2

group group1 40
tc_manual small1
tc_manual small2

group group2 60
include_group group1
include_group sample
tc_manual s1
tc_manual s2
tc_manual s3
