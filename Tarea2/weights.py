"""
C- Problem C
Nicolas Zapata Clavijo
8984273
"""
from sys import stdin

def emparejar(weights1, pesoMaximo):
    posiblesParejas = []
    ans = True
    for i in range(len(weights1)):
        if weights1[i] > pesoMaximo:
            posiblesParejas.append(weights1[i])
    for i in range(0, len(posiblesParejas), 2):
        if i + 1 >= len(posiblesParejas) or posiblesParejas[i] != posiblesParejas[i + 1]:
            ans = False
    return ans

def busquedaPesos(weights1, weights2, setPesas):
    listaPesas = []
    for pesas in setPesas:
        listaPesas.append(pesas)
    listaPesas.sort()
    left, right = 0, max(setPesas)
    ans = right
    while left <= right:
        mid = (left + right) // 2
        if emparejar(weights1, mid) and emparejar(weights2, mid):
            ans = mid
            right = mid - 1
        else:
            left = mid + 1
    return ans

def main():
    linea = stdin.readline()
    while linea:
        setPesas = set()
        weights1 = []
        weights2 = []
        peso = list(map(int, stdin.readline().split()))
        for i in peso:
            weights1.append(i)
            setPesas.add(i)
        peso = list(map(int, stdin.readline().split()))
        for i in peso:
            weights2.append(i)
            setPesas.add(i)
        print(busquedaPesos(weights1, weights2, setPesas))
        linea = stdin.readline()
main()

"""
En la función busquedaPesos primero ordeno setPesas que tiene una complejidad O(k log k) siendo k la cantidad de pesas unicas
Luego al ejecutar la busqueda binaria tenemos O(log M) siendo M el peso maximo en setPesas
Por ultimo en emparejar ambos bucles tienen complejidad de O(N)
Como llamo a emparejar dentro de la busqueda binaria la complejidad total seria O(N log M)

Entonces la complejidad total del codigo es O(N log M)  
"""