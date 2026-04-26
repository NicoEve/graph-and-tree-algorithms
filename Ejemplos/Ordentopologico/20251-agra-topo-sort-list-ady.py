"""
Implementación Algoritmos Orden Topológico
Marzo 8 de 2025

"""

from collections import deque

# n = |V|, m = |E|

# Orden topológico con DFS: Versión 1
# Se registra el tiempo de finalización y después del DFS se ordenan los nodos
# por tiempo de finalización de mayor a menor
# Complejidad: T(n, m) E O(n * log n)
def topoSortAux(u, G, vis):
  global t
  vis[u] = True
  t += 1
  desc[u] = t

  for w in G[u]:
    if not vis[w]:
      topoSortAux(w, G, vis)

  t += 1
  fin[u] = t

def topoSortDFS(G):
  global t, desc, fin, tree
  vis = [False for _ in range(len(G))]
  desc, fin = [None for _ in range(len(G))], [None for _ in range(len(G))]
  t = 0
  for u in range(len(G)):
    if not vis[u]:
      topoSortAux(u, G, vis)
  tmp = []
  for u in range(len(G)):
    tmp.append((u, fin[u]))
  tmp.sort(key = lambda x: x[1], reverse = True)
  topo = [u for u,_ in tmp]
  return topo

# Orden topológico con DFS: Versión 2
# No se registra el tiempo de finalización pero después de finalizar cada nodo
# este es agregado a una lista. El orden topológico es esa lista pero al reves.
# Complejidad: T(n, m) E O(n + m)
def topoSortAux2(u, G, vis, topo):
  global t
  vis[u] = True
  for w in G[u]:
    if not vis[w]:
      topoSortAux2(w, G, vis, topo)
  topo.append(u)
  
def topoSortDFS2(G):
  global t, desc, fin, tree
  vis = [False for _ in range(len(G))]
  t, topo = 0, []
  for u in range(len(G)):
    if not vis[u]:
      topoSortAux2(u, G, vis, topo)
  topo.reverse()
  return topo

# Orden topológico con DFS: Versión 3
# No se registra el tiempo de finalización pero después de finalizar cada nodo
# este es agregado a una lista doblemente enlazada en el frente.
# Complejidad: T(n, m) E O(n + m)
def topoSortAux3(u, G, vis, topo):
  global t
  vis[u] = True
  for w in G[u]:
    if not vis[w]:
      topoSortAux3(w, G, vis, topo)
  topo.appendleft(u)
  
def topoSortDFS3(G):
  global t, desc, fin, tree
  vis = [False for _ in range(len(G))]
  t, topo = 0, deque()
  for u in range(len(G)):
    if not vis[u]:
      topoSortAux3(u, G, vis, topo)
  return topo

# Orden topológico con BFS (Algoritmo de Kahn)
# Se obtiene el grado de incidencia de cada nodo y se agregan a una cola
# los nodos que tienen incidencia 0. Luego, para cada elemento que se saca
# de la cola se procesan sus elementos adyacentes y se les resta 1 en su grado
# de incidencia. Se agregan los nodos a la cola a medida que su incidencia pasa
# a ser 0.
# Complejidad: T(n, m) E O(n + m)
def topoSortKahn(G):
  inc, queue, topo = [0 for _ in range(len(G))], deque(), []
  for u in range(len(G)):
    for v in G[u]:
      inc[v] += 1
  for u in range(len(G)):
    if inc[u] == 0:
      queue.append(u)
  while len(queue) > 0:
    u = queue.popleft()
    topo.append(u)
    for v in G[u]:
      inc[v] -= 1
      if inc[v] == 0:
        queue.append(v)

  if len(topo) == len(G): ans = topo
  else: ans = []
  return ans
 
def main():
  # Grafo en las anotaciones de clase
  G = [[1, 5, 3, 2], [2, 3], [], [4], [2], [1]]
  ans = topoSortDFS(G)
  print(*ans)
  ans = topoSortDFS2(G)
  print(*ans)
  ans = topoSortDFS3(G)
  print(*ans)
  ans = topoSortKahn(G)
  print(*ans)

  G = [[1, 5, 3, 2], [2, 3], [], [4, 0], [2], [1]]
  ans = topoSortKahn(G)
  print(*ans)
  
main()
