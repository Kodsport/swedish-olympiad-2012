#!/usr/bin/env python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

seed = int(cmdlinearg('seed', sys.argv[-1]))
n = int(cmdlinearg('n'))

random.seed(seed)

def r():
    m = 10**6 - 1
    return random.randint(-m, m)

print(n)
for i in range(n):
    print(r(), r(), r(), r())
