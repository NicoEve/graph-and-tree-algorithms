"""
Implementación Búsqueda Binaria
Carlos Ramírez
Febrero 4 de 2025

"""

def solve(l, r, v, A):
  if r - l == 1: ans = A[l] == v
  else:
    mid = (l + r) // 2
    if v < A[mid]:
      ans = solve(l, mid, v, A)
    else:
      ans = solve(mid, r, v, A)
  return ans

def solveIter(v, A):
  l, r = 0, len(A)
  while r - l > 1:
    mid = (l + r) // 2
    if v < A[mid]: r = mid
    else: l = mid
  ans = A[l] == v
  return ans
            
