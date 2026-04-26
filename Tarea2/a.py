def emparejar(weights1, weights2, pesoMaximo):
    ans = True
    posiciones = {}
    i = 0
    while i < len(weights1):
        w = weights1[i]
        if w not in posiciones:
            posiciones[w] = []
        posiciones[w].append((0, i))
        i += 1
    i = 0
    while i < len(weights2):
        w = weights2[i]
        if w not in posiciones:
            posiciones[w] = []
        posiciones[w].append((1, i))
        i += 1
    for weight in posiciones:
        posList = posiciones[weight]
        row1, index1 = posList[0]
        row2, index2 = posList[1]
        if row1 != row2 and weight > pesoMaximo:
            ans = False
        elif row1 == row2:
            if index2 - index1 > 1:
                index1 = index1 + 1
                while index1 < index2 - 1:
                    if weights1[index1] <= pesoMaximo:
                        ans = False
                    index1 += 1
    return ans