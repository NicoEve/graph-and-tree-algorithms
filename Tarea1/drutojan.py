from collections import deque

"""
C-Problem C
Nicolas Zapata
8984273
"""

class TroubleMaker:
    def __init__(self):
        self.nombre = ""
        self.minutos = 0
        self.cola = deque()

def minutosSentado(m, n, nombre, listaClase):
    tiempoTotal = n
    tiempoDeCambio = 2
    continuar = True
    personaActual = None
    for trouble in listaClase:
        if trouble.nombre == nombre:
            personaActual = trouble
    while continuar:
        tiempoSentado = min(m, tiempoTotal)
        personaActual.minutos += tiempoSentado
        tiempoTotal -= tiempoSentado
        if tiempoTotal <= 0:
            continuar = False
        else:
            if tiempoTotal >= tiempoDeCambio:
                tiempoTotal -= tiempoDeCambio
                siguientePersona = personaActual.cola.popleft()
                personaActual.cola.append(siguientePersona)
                for trouble in listaClase:
                    if trouble.nombre == siguientePersona:
                        personaActual = trouble
            else:
                continuar = False
    return listaClase

def main():
    i = 1
    listaClase = []
    nombres = ["Ja", "Sam", "Sha", "Sid", "Tan"]
    for nombre in nombres:
        trouble = TroubleMaker()
        trouble.nombre = nombre
        listaClase.append(trouble)
    numCases = int(input())
    while i <= numCases:
        for trouble in listaClase:
            trouble.minutos = 0
        m, n, nombre = input().split()
        m, n = int(m), int(n)
        for trouble in listaClase:
            trouble.cola = deque(input().split()[1:])
        resultado = minutosSentado(m, n, nombre, listaClase)
        print(f"Case {i}:")
        for trouble in resultado:
            print(f"{trouble.nombre} {trouble.minutos}")
        i += 1
if __name__ == "__main__":
    main()

"""
La complejidad de la función en O(1) porque estamos usando un ciclo que se va a ejecutar n veces y las funciones que usamos
son O(1) entonces estas no afectan la complejidad
"""