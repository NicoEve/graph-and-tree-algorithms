"""
Nicolas Zapata Clavijo
8984273
D-Problem D
"""
import sys

def main():
    datos = sys.stdin.read().split()
    indice = 0
    t = int(datos[indice])
    indice += 1
    salida = []
    salida.append("SHIPPING ROUTES OUTPUT")
    for caso in range(1, t + 1):
        m = int(datos[indice])
        indice += 1
        n = int(datos[indice])
        indice += 1
        p = int(datos[indice])
        indice += 1
        posiciones = {}
        for i in range(m):
            posiciones[datos[indice]] = i
            indice += 1
        INF = 10**9
        dist = [[INF for _ in range(m)] for _ in range(m)]
        for i in range(m):
            dist[i][i] = 0
        for _ in range(n):
            a = datos[indice]
            indice += 1
            b = datos[indice]
            indice += 1
            u = posiciones[a]
            v = posiciones[b]
            dist[u][v] = 1
            dist[v][u] = 1
        for k in range(m):
            for i in range(m):
                for j in range(m):
                    if dist[i][k] + dist[k][j] < dist[i][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]
        salida.append("")
        salida.append("DATA SET " + str(caso))
        salida.append("")
        for _ in range(p):
            tam = int(datos[indice])
            indice += 1
            a = datos[indice]
            indice += 1
            b = datos[indice]
            indice += 1
            u = posiciones[a]
            v = posiciones[b]
            if dist[u][v] == INF:
                salida.append("NO SHIPMENT POSSIBLE")
            else:
                salida.append("$" + str(tam * dist[u][v] * 100))
    salida.append("")
    salida.append("END OF OUTPUT")
    sys.stdout.write("\n".join(salida))
main()

"""
Estoy usando bsf que tiene una complejidad O(n + m), sin embargo al estoy usando para cada pedido p que tengo en la lista
por lo tanto la complejidad total es O(p(n + m)), siendo p el numero de pedidos, m el numero de almacenes y n las aristas
"""