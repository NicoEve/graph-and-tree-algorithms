import heapq
import sys

"""
E-Problem E
Nicolas Zapata
8984273
"""

def encontrarCartas(listaCartas, num2):
    contador = {}
    for label, number in listaCartas:
        if (label, number) in contador:
            contador[(label, number)] += 1
        else:
            contador[(label, number)] = 1
    heap = [(-count, -number, label) for (label, number), count in contador.items()]
    heapq.heapify(heap)
    cartasRepetidas = []
    for _ in range(num2):
        if heap:
            count, number, label = heapq.heappop(heap)
            cartasRepetidas.append((label, -number, -count))
    cartasRepetidas.sort()
    return cartasRepetidas

def main():
    input = sys.stdin.read
    data = input().splitlines()
    i = 0
    flag = False
    while i < len(data) and not flag:
        num1, num2 = map(int, data[i].split())
        if num1 == 0 and num2 == 0:
            flag = True
        i += 1
        listaCartas = []
        for _ in range(num1):
            label, number = data[i].split()
            listaCartas.append((label, int(number)))
            i += 1
        cartasRepetidas = encontrarCartas(listaCartas, num2)
        for label, number, count in cartasRepetidas:
            print(f"{label} {count}")

if __name__ == '__main__':
    main()

"""
La Complejidad de este codigo es O (n*log n), porque el ciclo for en donde extraigo los elementos más grandes del heap es O(n*log n) y la función sort 
también tiene la misma complejdiad
"""