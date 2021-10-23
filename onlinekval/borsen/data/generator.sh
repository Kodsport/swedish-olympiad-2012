#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution borsen_js.cc

samplegroup
limits maxn=14
sample sample01

group group1 30
limits maxn=14
include_group sample
tc_manual ../manual/borsen01.in
tc_manual ../manual/borsen02.in
tc_manual ../manual/borsen03.in

group group2 40
limits maxn=1000
include_group group1
tc_manual ../manual/borsen04.in
tc_manual ../manual/borsen05.in
tc_manual ../manual/borsen06.in
tc_manual ../manual/borsen07.in

group group3 30
limits maxn=100000
include_group group2
tc_manual ../manual/borsen08.in
tc_manual ../manual/borsen09.in
tc_manual ../manual/borsen10.in
