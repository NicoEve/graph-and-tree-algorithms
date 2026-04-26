"""
Nicolas Zapata Clavijo
8984273
B-Problem B
"""

"""
Estoy ejecutando el algoritmo de kosaraju cuya complejidad es O(n + m), siendo n el numero de nodos y m el numero de aristas,
luego en minDomino también recorro las aristas del grafo lo cual también es O(n + m), por lo cual la complejidad final de mi algoritmo
es O(n + m)
"""

from sys import stdin, setrecursionlimit
from collections import deque

setrecursionlimit(10 ** 6)
MAX = 100001
adj, adjT = [[] for _ in range(MAX)], [[] for _ in range(MAX)]
n, m = 0, 0
visitados, sccInd = [False] * MAX, [-1] * MAX
ord = deque()
numSCC = 0
sccNodos = []

def kosaraju():
    global numSCC
    for i in range(1, n + 1):
        if not visitados[i]:
            kosarajuAux(i)
    for i in range(1, n + 1):
        sccInd[i] = -1
    numSCC = 0
    for v in ord:
        if sccInd[v] == -1:
            numSCC += 1
            sccNodos.append([])
            asignar(v, numSCC)

def kosarajuAux(v):
    if not visitados[v]:
        visitados[v] = True
        for vecino in adj[v]:
            kosarajuAux(vecino)
        ord.appendleft(v)

def asignar(u, num):
    sccInd[u] = num
    sccNodos[num - 1].append(u)
    for vecino in adjT[u]:
        if sccInd[vecino] == -1:
            asignar(vecino, num)

def minDominos():
    ans = 0
    sccInDegree = [0] * numSCC
    for v in range(1, n + 1):
        for w in adj[v]:
            if sccInd[v] != sccInd[w]:
                sccInDegree[sccInd[w] - 1] += 1
    for i in range(numSCC):
        if sccInDegree[i] == 0:
            ans += 1
    return ans

def main():
    global n, m
    numCases = int(stdin.readline().strip())
    for _ in range(numCases):
        n, m = map(int, stdin.readline().split())
        for i in range(n + 1):
            adj[i].clear()
            adjT[i].clear()
        for i in range(n + 1):
            visitados[i] = False
            sccInd[i] = -1
        ord.clear()
        sccNodos.clear()
        for _ in range(m):
            u, v = map(int, stdin.readline().split())
            adj[u].append(v)
            adjT[v].append(u)
        kosaraju()
        print(minDominos())

main()