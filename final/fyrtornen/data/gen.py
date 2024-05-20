import sys
import random
import math

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
k = int(cmdlinearg('k'))

print(n, m, k)
seen = set()
for i in range(m):
    while 1:
        a,b = random.randint(0, n-1),random.randint(0, n-1)
        if (a,b) in seen:
            continue
        seen.add((a,b))
        print(a,b)
        break
