def lower_bound(a, v):
    l, r = 0, len(a)
    while r - l > 1:
        mid = (l + r) // 2
        if a[mid] < v:
            l = mid
        else:
            r = mid
    return r

def upper_bound(a, v):
    l, r = 0, len(a)
    while r - l > 1:
        mid = (l + r) // 2
        if a[mid] <= v:
            l = mid
        else:
            r = mid
    return r

def contar_reps(a, v):
    izquierda = lower_bound(a, v)
    derecha = upper_bound(a, v)
    if izquierda == len(a) or a[izquierda] != v:
        ans = 0
    else:
        ans = derecha - izquierda
    return ans