#!/usr/bin/python3
import sys, re

posint = "([1-9][0-9]*)"

line = sys.stdin.readline()
assert re.compile("^"+posint+"$").match(line) is not None, "First line not a positive integer"

N = int(line)

assert 1 <= N <= 10, "N is out of bounds"

line = sys.stdin.readline()
match = re.compile("^"+posint+"(?: "+posint+"){"+str(N-1)+"}$").match(line)
assert match is not None, "Second line does not consist of %d positive integers."%N

for num in match.groups():
	assert 1 <= int(num) <= 1000000, "Number too big"

assert len(sys.stdin.readline()) == 0, "Garbage input"
sys.exit(42)
