from collections import deque

def bfs_aux(g, colores, vis, u):
    q = deque()
    q.append(u)
    vis[u] = True
    ans = True
    while len(q) != 0 and ans:
        v = q.popleft()
        for w in g[v]:
            if colores[v] == colores[w]:
                ans = False
            else:
                if not vis[w]:
                    vis[w] = True
                    q.append(w)
    return ans

def bfs(g, colores):
    vis = [False for _ in range(len(g))]
    es_bipartito = True
    for u in range (len(g)):
        if not vis[u]:
            if not bfs_aux(g, colores, vis, u):
                es_bipartito = False
    return es_bipartito