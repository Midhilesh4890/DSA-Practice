import sys
from collections import *
from itertools import *
from heapq import *
from functools import *
import os
from bisect import *
import random
# Set input and output paths
try:
    sys.stdin = open('D:\\Projects\\DSA Practice\\inp.txt', 'r')
    sys.stdout = open('D:\\Projects\\DSA Practice\\out.txt', 'w')
except FileNotFoundError:
    pass
    
# Utility Functions
def find_factors(n):
    factors = set()
    for i in range(1, int(n**0.5) + 1):
        if n % i == 0:
            factors.add(i)
            factors.add(n // i)
    return list(factors)
 
def sieve(limit):
    primes = list(range(limit + 1))
    for i in range(2, int(limit**0.5) + 1):
        if primes[i] == i:
            for j in range(i * i, limit + 1, i):
                primes[j] = i
    return primes
 
def count_factors(n):
    count = 0
    for i in range(1, int(n**0.5) + 1):
        if n % i == 0:
            count += 1 if i == n // i else 2
    return count
 
def nth_prime(n):
    limit = max(15, int(n * (log(n) + log(log(n))))) + 10
    spf = list(range(limit + 1))
    for i in range(2, int(limit**0.5) + 1):
        if spf[i] == i:
            for j in range(i * i, limit + 1, i):
                if spf[j] == j:  # only mark if not already marked
                    spf[j] = i
    
    count = 0
    for i in range(2, limit + 1):
        if spf[i] == i:  # i is prime
            count += 1
            if count == n:
                return i
 
def prime_factors_count(n, primes):
    factors_count = defaultdict(int)
    while n > 1:
        smallest_prime = primes[n]
        factors_count[smallest_prime] += 1
        n //= smallest_prime
    return sum(factors_count.values())
 
def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def mex(arr):
    if not arr:
        return 0
    maxval = max(arr)
    curr = [False] * (maxval + 2)
    for x in arr:
        if 0 <= x <= maxval:
            curr[x] = True
    for i in range(len(curr)):
        if not curr[i]:
            return i
    return maxval + 1
 
# Custom hash function for python instead of dict and defaultdict for faster execution
class HashedInt:
    FIXED_RANDOM = 0x9e3779b97f4a7c15

    def __init__(self, val):
        self.val = val

    def __eq__(self, other):
        return self.val == other.val

    def __hash__(self):
        x = self.val + HashedInt.FIXED_RANDOM
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb
        return x ^ (x >> 31)

class Treap:

    __slots__ = ("key", "prio", "left", "right")
    def __init__(self, key):
        self.key = key
        self.prio = random.getrandbits(30)
        self.left = None
        self.right = None

def split(root, key):
    if not root:
        return None, None
    if key <= root.key:
        l, r = split(root.left, key)
        root.left = r
        return l, root
    else:
        l, r = split(root.right, key)
        root.right = l
        return root, r

def merge(a, b):
    if not a or not b:
        return a or b
    if a.prio > b.prio:
        a.right = merge(a.right, b)
        return a
    else:
        b.left = merge(a, b.left)
        return b

def insert(root, node):
    if not root:
        return node
    if node.prio > root.prio:
        l, r = split(root, node.key)
        node.left = l
        node.right = r
        return node
    if node.key < root.key:
        root.left = insert(root.left, node)
    else:
        root.right = insert(root.right, node)
    return root

def find_predecessor(root, key):
    res = None
    while root:
        if root.key < key:
            res = root
            root = root.right
        else:
            root = root.left
    return res

def find_successor(root, key):
    res = None
    while root:
        if root.key > key:
            res = root
            root = root.left
        else:
            root = root.right
    return res

def kmp_first_occurrence(text: str, pat: str) -> int:
    """
    Return first index where pat appears in text, or -1.
    Classic KMP: O(len(text) + len(pat))
    """
    m = len(pat)
    n = len(text)

    # Build lPS (longest prefix which is also suffix)
    lps = [0] * m
    j = 0  # length of curr matched prefix
    for i in range(1, m):
        # fall back while mismatch
        while j > 0 and pat[i] != pat[j]:
            j = lps[j - 1]
        if pat[i] == pat[j]:
            j += 1
            lps[i] = j

    # Search
    j = 0  # current match length in pat
    for i in range(n):
        while j > 0 and text[i] != pat[j]:
            j = lps[j - 1]
        if text[i] == pat[j]:
            j += 1
            if j == m:
                # pattern ends at i
                return i - m + 1
    return -1

INF = 10**30

class AhoFirst:
    __slots__ = ("next", "link", "children", "first_end", "pat_node", "pat_len")
    def __init__(self, k):
        self.next = [dict()]       # transitions per node: {ord(ch): nxt}
        self.link = [0]            # suffix link; link[0] = 0
        self.children = [[]]       # suffix-link tree children
        self.first_end = [INF]     # earliest end index visited at this node
        self.pat_node = [0]*k      # terminal node for each pattern
        self.pat_len  = [0]*k

    def _new_node(self):
        self.next.append({})
        self.link.append(0)
        self.children.append([])
        self.first_end.append(INF)
        return len(self.next) - 1

    def add_pattern(self, pat, idx):
        v = 0
        for ch in pat:
            c = ord(ch)
            nv = self.next[v].get(c)
            if nv is None:
                nv = self._new_node()
                self.next[v][c] = nv
            v = nv
        self.pat_node[idx] = v
        self.pat_len[idx] = len(pat)

    def build(self):
        q = deque()
        # init depth-1 links and root children in suffix-tree
        for c, u in self.next[0].items():
            self.link[u] = 0
            self.children[0].append(u)
            q.append(u)

        while q:
            v = q.popleft()
            for c, u in self.next[v].items():
                q.append(u)
                j = self.link[v]
                while j and c not in self.next[j]:
                    j = self.link[j]
                self.link[u] = self.next[j].get(c, 0)
                self.children[self.link[u]].append(u)

    def search_first(self, text):
        v = 0
        ntrans = self.next
        link = self.link
        first_end = self.first_end

        for i, ch in enumerate(text):
            c = ord(ch)
            while v and c not in ntrans[v]:
                v = link[v]
            v = ntrans[v].get(c, 0)
            if first_end[v] == INF:
                first_end[v] = i  # store earliest end position for this node

        # propagate minima bottom-up on suffix-link tree
        order = []
        stack = [0]
        while stack:
            x = stack.pop()
            order.append(x)
            stack.extend(self.children[x])

        for x in reversed(order[1:]):  # skip root at index 0
            p = link[x]
            if first_end[x] < first_end[p]:
                first_end[p] = first_end[x]

        # build ans
        ans = []
        for node, plen in zip(self.pat_node, self.pat_len):
            fe = self.first_end[node]
            if fe == INF:
                ans.append(-1)
            else:
                ans.append(fe - plen + 2)  # 1-based
        return ans

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, x):
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x

    def union(self, a, b):
        ra, rb = self.find(a), self.find(b)
        if ra == rb:
            return ra
        if self.size[ra] < self.size[rb]:
            ra, rb = rb, ra
        self.parent[rb] = ra
        self.size[ra] += self.size[rb]
        return ra