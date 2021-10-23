#!/usr/bin/env bash

REQUIRE_SAMPLE_REUSE=0 # insufficient sample precision
. ../../../../testdata_tools/gen.sh

use_solution sol_ld.cpp

compile gen_random.py

samplegroup
sample_manual 1

group group1 20
tc one1 gen_random n=1
tc one2 gen_random n=1
tc one3 gen_random n=1
tc one4 gen_random n=1
tc one5 gen_random n=1

group group2 40
tc small1 gen_random n=5
tc small2 gen_random n=5
tc small3 gen_random n=5
tc small4 gen_random n=5
tc small5 gen_random n=5
tc small6 gen_random n=5

group group3 40
tc c1 gen_random n=15
tc c2 gen_random n=15
tc c3 gen_random n=15
tc c4 gen_random n=15
tc c5 gen_random n=15
tc c6 gen_random n=15
tc c7 gen_random n=15
tc c8 gen_random n=15
