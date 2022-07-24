#!/usr/bin/env pypy3

import math

def dst(dx, dy): return math.sqrt(dx*dx + dy*dy)

N = int(input())
x = [0] * (2*N)
y = [0] * (2*N)
for i in range(N):
    x[i * 2], y[i * 2], x[i * 2 + 1], y[i * 2 + 1] = map(int, input().split())

T = [[-1.0] * 2**N for _ in range(2 * N)]
P = [[0] * 2**N for _ in range(2 * N)]

for now in range(2 * N):
    T[now][-1] = dst(x[now], y[now])
    P[now][-1] = -2

for vis in range(2 ** N - 2, 0, -1):
    for now in range(2 * N):
        at = now // 2
        if not (vis & (1 << at)): continue
        best = 1e100
        xx = x[now]
        yy = y[now]
        for i in range(N):
          if not (vis & (1 << i)):
              for j in range(2):
                k = i * 2 + j
                d = dst(xx - x[k], yy - y[k]) + T[k][vis | (1<<i)]
                if d < best:
                   best = d
                   nx = i * 2 + j
        assert nx != -1
        T[now][vis] = best
        P[now][vis] = nx

T[0][0] = 1e18
for now in range(2 * N):
    ndist = dst(x[now], y[now]) + T[now][1 << (now // 2)]
    if ndist < T[0][0]:
        T[0][0] = ndist
        P[0][0] = now

print(T[0][0])

now = 0
vis = 0
for i in range(N):
    j = P[now][vis]
    print(j // 2 + 1, j % 2 + 1)
    now = j
    vis |= 2 ** (j // 2)
