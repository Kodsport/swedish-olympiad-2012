#!/usr/bin/env bash

REQUIRE_SAMPLE_REUSE=0
. ../../../../../testdata_tools/gen.sh

use_solution js.cpp

samplegroup
sample 1
sample 2
sample 3
sample 4

group group1 50
limits notie=1
tc_manual ../manual/v1.in
tc_manual ../manual/v2.in
tc_manual ../manual/v3.in
tc_manual ../manual/v4.in
tc_manual ../manual/v5.in
tc_manual ../manual/v6.in
tc_manual ../manual/s1.in
tc_manual ../manual/s3.in
tc_manual ../manual/s4.in

group group2 50
include_group group1
tc_manual ../manual/tie1.in
tc_manual ../manual/tie2.in
tc_manual ../manual/tie3.in
tc_manual ../manual/s2.in
