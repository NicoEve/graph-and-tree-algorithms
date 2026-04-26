from sys import stdin

MAX = 10000
adj = [[] for i in range(MAX)]
visitado, low = [0 for i in range(MAX)], [-1 for i in range(MAX)]
enPila = [False for i in range(MAX)]
n, t, numSCC = int(), 0, 0
sccNodos, pila = [], []

def tarjan():
    for i in range(n):
        low[i], visitado[i], enPila[i] = -1, -1, False

    for i in range(n):
        if visitado[i] == -1:
            tarjanAux(i)

def tarjanAux(v):
    global t, numSCC
    t += 1
    visitado[v], low[v] = t, t
    pila.append(v)
    enPila[v] = True

    for i in range(len(adj[v])):
        w = adj[v][i]
        if visitado[w] == -1:
            tarjanAux(w)
            low[v] = min(low[v], low[w])
        elif enPila[w]:
            low[v] = min(low[v], visitado[w])

    if low[v] == visitado[v]:
        print("SCC con índice %d: " % low[v], end = '')
        sccNodos.append([])
        numSCC += 1
        while pila[-1] != v:
            a = pila.pop()
            print("%d " % a, end = '')
            enPila[a] = False
            sccNodos[numSCC - 1].append(a)

        a = pila.pop()
        print("%d " % a)
        enPila[a] = False
        sccNodos[numSCC - 1].append(a)

def main():
    global n
    n, m = list(map(int, stdin.readline().split()))

    for i in range(m):
        u, v = list(map(int, stdin.readline().split()))
        adj[u].append(v)

    print("Grafo")
    for i in range(n):
        print("Nodo %d:" % i)
        for j in range(len(adj[i])):
            print("%d" % adj[i][j], end = ' ')
        print("")

    print("Componentes Fuertemente Conexos:")
    tarjan()

main()