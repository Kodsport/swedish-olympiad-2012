#!/usr/bin/env bash

PPATH=$(realpath ..)
REQUIRE_SAMPLE_REUSE=0
. ../../../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution uppg4.cpp
compile gen_random.py

samplegroup
limits maxw=20 maxbsum=60
sample 1
sample 2
sample 3
sample 4

group group1 66
limits maxw=10 maxbsum=25
tc 1
tc 2
tc 4
tc_manual g1
tc_manual g2
tc rnd-small-1 gen_random maxw=10 maxbsum=25
tc rnd-small-2 gen_random maxw=10 maxbsum=25
tc rnd-small-3 gen_random maxw=10 maxbsum=25
tc rnd-small-4 gen_random maxw=10 maxbsum=25
tc rnd-small-5 gen_random maxw=10 maxbsum=25
tc rnd-small-6 gen_random maxw=10 maxbsum=25

group group2 34
limits maxw=20 maxbsum=60
include_group group1
tc_manual g3
tc 3
tc rnd-1 gen_random maxw=20 maxbsum=60
tc rnd-2 gen_random maxw=20 maxbsum=60
tc rnd-3 gen_random maxw=20 maxbsum=60
tc rnd-4 gen_random maxw=20 maxbsum=60
tc rnd-5 gen_random maxw=20 maxbsum=60
tc rnd-6 gen_random maxw=20 maxbsum=60
