import sys
try:
    sys.stdin = open('D:\\Projects\\DSA Practice\\inp.txt', 'r')
    sys.stdout = open('D:\\Projects\\DSA Practice\\out.txt', 'w')
except FileNotFoundError:
    pass

from itertools import *
from collections import *
from heapq import *
from functools import *
import os
from bisect import *
import random
from math import *
import builtins
from array import array
import re

input = sys.stdin.buffer.readline
si = lambda: input().decode().strip()
ii = lambda: int(input())
li = lambda: list(map(int, input().split()))
ls = lambda: input().split()

sys.setrecursionlimit(10**6)

MOD = 10**9 + 7

def solve():
    n = ii()
    a = li()

    mask = 0
    res = 0

    for x in a:
        if (mask >> x) & 1:
            res -= x
        else:
            res += x

        mask ^= 1 << x

    print(res)

if __name__ == "__main__":
    solve()