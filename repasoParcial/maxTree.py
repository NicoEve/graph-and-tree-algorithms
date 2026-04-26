"""
n, MAXN = int(), 1000
tree = [None for _ in range(MAXN) * 2]
pend = [0 for _ in range(MAXN) * 2]

def build(a, v, l, r):
    if l == r: tree[v] = a[l]
    else:
        m = l + ((r - l) >> 1)
        build(a, v + 1, l, m)
        build(a, v + 2 * (m - l + 1), m + 1, r)
        tree[v] = max(tree[v + 1], tree[v + 2 * (m - l + 1)])

def query(v, L, R, l, r):
    ans = None
    if l > r: ans = float('inf')
    elif l == L and r == R: ans = tree[v]
    else:
        m = L + ((R - L) >> 1)
        push(v, v + 1, v + 2 * (m - L + 1))
        ans = max(query(v + 1, L, m, l, min(r, m)), query(v + 2 * (m - L + 1), m + 1, R, max(l, m + 1), r))
    return ans

def update(v, L, R, l, r, h):
    if l <= r:
        if l == L and r == R: tree[v] += h; pend[v] += h
        else:
            m = L + ((R - L) >> 1)
            push(v, v + 1, v + 2 * (m - L + 1))
            update(v + 1, L, m, l, min(r, m), h)
            update(v + 2 * (m - L + 1), m + 1, R, max(l, m + 1), r, h)
            tree[v] = max(tree[v + 1], tree[v + 2 * (m - L + 1)])

def push(v, v1, v2):
    tree[v1] += pend[v]
    pend[v1] += pend[v]
    tree[v2] += pend[v]
    pend[v2] += pend[v]
    pend[v] = 0
"""

n, MAXN = int(), 1000
tree = [0 for _ in range(MAXN * 2)]

def build(a, v, l, r, buscado):
    if l == r: tree[v] = 1 if a[l] == buscado else 0
    else:
        m = l + ((r - l) >> 1)
        build(a, v + 1, l, m, buscado)
        build(a, v + 2 * (m - l + 1), m + 1, r, buscado)
        tree[v] = tree[v + 1] + tree[v + 2 * (m - l + 1)]

def sum(v, L, R, l, r):
    ans = None
    if l > r: ans = 0
    elif l == L and r == R: ans = tree[v]
    else:
        m = L + ((R - L) >> 1)
        ans = sum(v + 1, L, m, l, min(r, m)) + sum(v + 2 * (m - L + 1), m + 1, R, max(l, m + 1), r)
    return ans

def update(v, L, R, pos, h):
    if L == R: tree[v] = h
    else:
        m = L + ((R - L) >> 1)
        if pos <= m: update(v + 1, L, m, pos, h)
        else: update(v + 2 * (m - L + 1), m + 1, R, pos, h)
        tree[v] = tree[v + 1] + tree[v + 2 * (m - L + 1)]

def encontrarPos(a, k):
    n = len(a)
    l, r = 0, n - 1
    res = -1
    while l <= r:
        m = (l + r) >> 1
        cnt = sum(0, 0, n - 1, 0, m)
        if cnt >= k:
            res = m
            r = m - 1
        else:
            l = m + 1
    return res