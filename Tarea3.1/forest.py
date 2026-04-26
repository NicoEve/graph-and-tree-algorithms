"""
Nicolas Zapata Clavijo
8984273
B-Problem B
"""

import sys

direcciones = [(0, 1), (0, -1), (1, 0), (-1, 0)]

def dfsAux(i, j, forest, vis, especie, n, m):
    vis[i][j] = True
    _, altura = forest[i][j].split('#')
    altura = int(altura)
    maxAltura = altura
    for di, dj in direcciones:
        ni, nj = i + di, j + dj
        if 0 <= ni < n and 0 <= nj < m and not vis[ni][nj]:
            especieVecina, _ = forest[ni][nj].split('#')
            if especieVecina == especie:
                maxAltura = max(maxAltura, dfsAux(ni, nj, forest, vis, especie, n, m))
    return maxAltura

def dfs(forest, n, m):
    vis = [[False] * m for _ in range(n)]
    alturasMaximas = []
    for i in range(n):
        for j in range(m):
            if not vis[i][j]:
                especie, _ = forest[i][j].split('#')
                alturaMaxima = dfsAux(i, j, forest, vis, especie, n, m)
                alturasMaximas.append((especie, alturaMaxima))
    alturasMaximas.sort()
    return alturasMaximas

def main():
    t = int(sys.stdin.readline().strip())
    for test_case in range(1, t + 1):
        n, m = map(int, sys.stdin.readline().split())
        forest = [sys.stdin.readline().split() for _ in range(n)]
        result = dfs(forest, n, m)
        print(f"Forest #{test_case}")
        for especie, altura in result:
            print(especie, altura)

main()

"""
como estoy usando dfs en una matriz, tenemos que la complejidad de busqueda en una matriz es O(n * m), ya que tengo que recorrer 
toda la matriz, por lo tanto la complejidad es O(n * m)
"""