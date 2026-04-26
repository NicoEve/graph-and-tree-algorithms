"""
Nicolás Zapata Claviji
8984273
C-Problem C
"""
"""
Usualmente la complejidad del algoritmo de bellmanFordMoore es de O(n * m) siendo n el número de nodos y m el número de aristas,
sin embargo en esta implementación el algoritmo la cantidad de iteraciones depende el número maximo de paradas que va a tomar Brett,
el cilo principal se ejecuta k + 1 veces, siendo k el número maximo de paradas y el ciclo interno tendría una complejidad de O(n + m) siendo
n el número de nodos y m el número de aristas, por lo que la complejidad final es O(k(n + m))
"""
from sys import stdin
import sys

def bellmanFordMoore(G, s, consultas):
    maxVuelos = consultas + 1
    d = [[float("inf")] * len(G) for _ in range(maxVuelos + 1)]
    d[0][s] = 0
    for k in range(maxVuelos):
        for u in range(len(G)):
            if d[k][u] != float("inf"):
                if d[k][u] < d[k + 1][u]:
                    d[k + 1][u] = d[k][u]
                for v, wuv in G[u]:
                    if d[k][u] + wuv < d[k + 1][v]:
                        d[k + 1][v] = d[k][u] + wuv
    return d

def main():
    lineas = sys.stdin.read().splitlines()
    idx = 0
    while idx < len(lineas) and lineas[idx].strip() == "":
        idx += 1
    t = int(lineas[idx].strip())
    idx += 1
    for escenario in range(1, t + 1):
        while idx < len(lineas) and lineas[idx].strip() == "":
            idx += 1
        N = int(lineas[idx].strip())
        idx += 1
        mapeo = {}
        ciudades = []
        for i in range(N):
            nombre = lineas[idx].strip()
            mapeo[nombre] = i
            ciudades.append(nombre)
            idx += 1
        M = int(lineas[idx].strip())
        idx += 1
        adj = [[] for _ in range(N)]
        for i in range(M):
            u, v, p = lineas[idx].split()
            u, v, p = mapeo[u], mapeo[v], int(p)
            adj[u].append((v, p))
            idx += 1
        lineaConsultas = list(map(int, lineas[idx].split()))
        idx += 1
        consultas = lineaConsultas[1:]
        maximoParadas = 0
        if len(consultas) > 0:
            maximoParadas = max(consultas)
        s = mapeo["Calgary"]
        d = mapeo["Fredericton"]
        costos = bellmanFordMoore(adj, s, maximoParadas)
        print(f"Scenario #{escenario}")
        for parada in consultas:
            limite = parada + 1
            if limite > len(costos) - 1:
                limite = len(costos) - 1
            costo = float("inf")
            for i in range(limite + 1):
                if costos[i][d] < costo:
                    costo = costos[i][d]
            if costo == float("inf"):
                print("No satisfactory flights")
            else:
                print(f"Total cost of flight(s) is ${costo}")
        if escenario < t:
            print()
main()