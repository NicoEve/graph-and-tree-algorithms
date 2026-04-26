def dfsAux(v, vis, G):
    print(v)
    vis[v] = True
    for w in G[v]:
        if not vis[w]:
            dfsAux(w, vis, G)

def dfs(G):
    vis = [False for _ in range(len(G))]
    for u in range(len(G)):
        if not vis[u]:
            dfsAux(u, vis, G)