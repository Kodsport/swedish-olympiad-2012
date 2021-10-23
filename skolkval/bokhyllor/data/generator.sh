#!/usr/bin/env bash

PPATH=$(realpath ..)
REQUIRE_SAMPLE_REUSE=0
. ../../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution uppg4.cpp

samplegroup
limits maxw=20 maxbsum=60
sample 1
sample 2
sample 3
sample 4

group group1 33
limits maxw=10 maxbsum=25
tc_manual g1

group group2 33
limits maxw=10 maxbsum=25
tc_manual g2

group group3 34
limits maxw=20 maxbsum=60
tc_manual g3
