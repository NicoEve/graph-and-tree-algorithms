"""
D-Problem D
Nicolás Zapata Clavijo
8984273
"""

"""
En esta solución hago un BFS el cual tiene complejidad de O(n + m), sin embargo, lo ejecuto para cada estación importante por esto la complejidad de mi solución termina
siendo O(s(n + m)), siendo s el número de estaciones de importantes, n el número de nodos en el grafo y m el número de aristas.
"""
from sys import stdin
import heapq

INF = 10 ** 18

def dijkstra(adj, start, k):
    dist = [INF for _ in range(k)]
    dist[start] = 0
    heap = [(0, start)]
    while heap:
        d, u = heapq.heappop(heap)
        if d <= dist[u]:
            for v, w in adj[u]:
                if d + w < dist[v]:
                    dist[v] = d + w
                    heapq.heappush(heap, (dist[v], v))
    return dist

def main():
    t = int(stdin.readline().strip())
    for _ in range(t):
        n, s = map(int, stdin.readline().split())
        lineas = []
        apariciones = [0 for _ in range(n + 1)]
        for _ in range(s):
            linea = list(map(int, stdin.readline().split()))
            linea.pop()
            lineas.append(linea)
            for x in linea:
                apariciones[x] += 1
        importantes = []
        for i in range(1, n + 1):
            if apariciones[i] > 1:
                importantes.append(i)
        k = len(importantes)
        indice = {}
        for i in range(k):
            indice[importantes[i]] = i
        adj = [[] for _ in range(k)]
        for linea in lineas:
            ultimaImportante = -1
            distanciaAcumulada = 0
            for i in range(len(linea)):
                estacion = linea[i]
                if apariciones[estacion] > 1:
                    if ultimaImportante != -1:
                        u = indice[ultimaImportante]
                        v = indice[estacion]
                        costo = distanciaAcumulada * 2
                        adj[u].append((v, costo))
                        adj[v].append((u, costo))
                    ultimaImportante = estacion
                    distanciaAcumulada = 0  
                if i + 1 < len(linea):
                    distanciaAcumulada += 1
        mejorEstacion = importantes[0]
        mejorSuma = INF
        for i in range(k):
            dist = dijkstra(adj, i, k)
            suma = 0
            for j in range(k):
                suma += dist[j]
            if suma < mejorSuma or (suma == mejorSuma and importantes[i] < mejorEstacion):
                mejorSuma = suma
                mejorEstacion = importantes[i]
        print("Krochanska is in: " + str(mejorEstacion))

main()