#!/usr/bin/python3
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
mode = cmdlinearg('mode')

pts = set()

def random_unused():
    while 1:
        a,b = random.randint(0, n-1),random.randint(0, n-1)
        if (a,b) not in pts:
            return (a,b)

if mode=="rand":
    while len(pts) < m:
        pts.add(random_unused())
elif mode=="stairs":
    pos = (0,0)
    for i in range(m):
        pts.add(pos)
        pos = (pos[0]+(i%2),pos[1]+((i+1)%2))
elif mode=="line":
    pos = (0,0)
    for i in range(m):
        pts.add(pos)
        pos = (pos[0]+1,pos[1])
elif mode=="midsize":
    sqrtm = int(m**0.5)
    cbrtm = int(m**0.333)

    # By pidgeonhole, we cant support this many medium components
    # Dump off most in a square top-left
    column_taken = [0] * (n)
    row_taken = [0] * (n)
    def add(a,b):
        pts.add((a,b))
        row_taken[a]=1
        column_taken[b]=1

    if m == 500000:
        sidelen = int(4e5**0.5)
        for i in range(sidelen):
            for j in range(sidelen):
                add(i,j)

    while len(pts) < m:
        compsz = random.randint(sqrtm-cbrtm, sqrtm+cbrtm)
        while 1:
            start = (random.randint(0,n-1), random.randint(0,n-1))
            if row_taken[start[0]] or column_taken[start[1]]:
                continue
            break
        add(start[0],start[1])
        for i in range(compsz-1):
            while 1:
                if random.randint(0,1):
                    np = (start[0],random.randint(0,n-1))
                else:
                    np = (random.randint(0,n-1),start[1])
                if np[0] != start[0] and row_taken[np[0]]: continue
                if np[1] != start[1] and column_taken[np[1]]: continue
                break
            add(np[0],np[1])
            start=np
    pts = list(pts)[:m]
else:
    assert 0

print(n, m, k)
for p in pts:
    print(*p)
