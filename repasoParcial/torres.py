from collections import deque
from math import sqrt

def distancia(p1, p2):
    return sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

def construir_grafo(estaciones):
    grafo = [[] for _ in range(len(estaciones))]
    for i in range(0, len(estaciones), 1):
        distancias = []
        for j in range(0, len(estaciones), 1):
            if i != j:
                dis = distancia(estaciones[i], estaciones[j])
                distancias.append((dis, estaciones[j][0], estaciones[j][1], j))
        distancias.sort()
        grafo[i].append(distancias[0][3])
        grafo[i].append(distancias[1][3])
    return grafo

def bfs(grafo):
    i = 0
    ans = True
    vis = [False for _ in range(len(grafo))]
    q = deque()
    q.append(0)
    vis[0] = True
    while len(q) > 0:
        v = q.popleft()
        for w in grafo[v]:
            if not vis[w]:
                vis[w] = True
                q.append(w)
    while i < len(vis) and ans:
        if not vis[i]:
            ans = False
        i += 1
    return ans

def se_conectan(estaciones):
    grafo = construir_grafo(estaciones)
    ans = bfs(grafo)
    return ans