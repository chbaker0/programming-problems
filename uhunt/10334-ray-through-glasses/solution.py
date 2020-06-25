#!/usr/bin/env python
import sys

fibs = [1, 2]
for i in range(2, 1001):
    fibs.append(fibs[i-1] + fibs[i-2])

for line in sys.stdin:
    idx = int(line)
    print(fibs[idx])
