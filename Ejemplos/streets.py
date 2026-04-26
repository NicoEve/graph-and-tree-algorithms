from sys import stdin
from collections import deque

INF = 10 ** 18

def lowerBound(arr, x):
    left = 0
    right = len(arr)
    ans = len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] >= x:
            ans = mid
            right = mid
        else:
            left = mid + 1
    return ans

def quitarRepetidos(arr):
    nueva = []
    if len(arr) > 0:
        nueva.append(arr[0])
        for i in range(1, len(arr)):
            if arr[i] != arr[i - 1]:
                nueva.append(arr[i])
    return nueva

def construirBloqueos(segmentos, xs, ys):
    ancho = len(xs) + 2
    alto = len(ys) + 2
    bloqueado = [[[0, 0, 0, 0] for _ in range(alto)] for _ in range(ancho)]
    for i in range(len(segmentos)):
        x1, y1, x2, y2 = segmentos[i]
        if x1 == x2:
            if y1 > y2:
                aux = y1
                y1 = y2
                y2 = aux
            cx = lowerBound(xs, x1) + 1
            cy1 = lowerBound(ys, y1) + 1
            cy2 = lowerBound(ys, y2) + 1
            y = cy1
            while y < cy2:
                bloqueado[cx - 1][y][0] = 1
                bloqueado[cx][y][1] = 1
                y += 1
        else:
            if x1 > x2:
                aux = x1
                x1 = x2
                x2 = aux
            cx1 = lowerBound(xs, x1) + 1
            cx2 = lowerBound(xs, x2) + 1
            cy = lowerBound(ys, y1) + 1
            x = cx1
            while x < cx2:
                bloqueado[x][cy - 1][2] = 1
                bloqueado[x][cy][3] = 1
                x += 1
    return bloqueado

def ceroUnoBfs(bloqueado, sx, sy, tx, ty, ancho, alto):
    dist = [[INF for _ in range(alto)] for _ in range(ancho)]
    cola = deque()
    dx = [1, -1, 0, 0]
    dy = [0, 0, 1, -1]
    dist[sx][sy] = 0
    cola.append((sx, sy))
    while len(cola) != 0:
        x, y = cola.popleft()
        for d in range(4):
            nx = x + dx[d]
            ny = y + dy[d]
            if 0 <= nx and nx < ancho and 0 <= ny and ny < alto:
                costo = bloqueado[x][y][d]
                if dist[x][y] + costo < dist[nx][ny]:
                    dist[nx][ny] = dist[x][y] + costo
                    if costo == 0:
                        cola.appendleft((nx, ny))
                    else:
                        cola.append((nx, ny))
    return dist[tx][ty]

def resolverCaso(segmentos, xCasa, yCasa, xUni, yUni):
    xs = []
    ys = []
    for i in range(len(segmentos)):
        x1, y1, x2, y2 = segmentos[i]
        xs.append(x1)
        xs.append(x2)
        ys.append(y1)
        ys.append(y2)
    xs.append(xCasa)
    xs.append(xUni)
    ys.append(yCasa)
    ys.append(yUni)
    xs.sort()
    ys.sort()
    xs = quitarRepetidos(xs)
    ys = quitarRepetidos(ys)
    ancho = len(xs) + 2
    alto = len(ys) + 2
    bloqueado = construirBloqueos(segmentos, xs, ys)
    sx = lowerBound(xs, xCasa) + 1
    sy = lowerBound(ys, yCasa) + 1
    tx = lowerBound(xs, xUni) + 1
    ty = lowerBound(ys, yUni) + 1
    ans = ceroUnoBfs(bloqueado, sx, sy, tx, ty, ancho, alto)
    return ans

def main():
    salida = []
    ciudad = 1
    linea = stdin.readline()
    while linea != "":
        linea = linea.strip()
        if linea != "":
            n = int(linea)
            if n != 0:
                segmentos = []
                for i in range(n):
                    x1, y1, x2, y2 = map(int, stdin.readline().split())
                    segmentos.append((x1, y1, x2, y2))
                xCasa, yCasa, xUni, yUni = map(int, stdin.readline().split())
                respuesta = resolverCaso(segmentos, xCasa, yCasa, xUni, yUni)
                salida.append("City " + str(ciudad))
                salida.append("Peter has to cross " + str(respuesta) + " streets")
                ciudad += 1
            else:
                linea = ""
        if linea != "":
            linea = stdin.readline()
    print("\n".join(salida))
main()