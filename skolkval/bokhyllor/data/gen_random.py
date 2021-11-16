#!/usr/bin/env pyhton3
import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
maxw = int(cmdlinearg('maxw'))
maxbsum = int(cmdlinearg('maxbsum'))
L = random.randint(min(20, maxbsum) // 2, min(20, maxbsum))
M = random.randint(0, min(20, maxbsum - L))
S = random.randint(0, min(20, maxbsum - L - M))

sw = random.randint(3, maxw)
print(S, M, L)
print(sw)
