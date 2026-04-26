from collections import deque

def bsfAux(u, vis, G):
    q = deque()
    q.append(u)
    vis[u] = True
    while len(q) != 0:
        v = q.popleft()
        print(v)
        for w in G[v]:
            if not vis[w]:
                vis[w] = True
                q.append(w) 

def bfs(G):
    vis = [False for _ in range(len(G))]
    for u in range(len(G)):
        if not vis[u]:
            bsfAux(u, vis, G)