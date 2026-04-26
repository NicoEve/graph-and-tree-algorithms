//
// Created by Nicolas on 28/01/2025.
//

#include <iostream>
#include <queue>
#include <map>

using namespace std;

int tiempoHorneo(queue<int> entry, queue<int> exit) {
    map<int, int> tiempos;  // Para contar las frecuencias de cada diferencia

    // Recorremos las entradas
    while (!entry.empty()) {
        int entryTimestamp = entry.front();
        entry.pop();

        // Comparamos esta entrada con todas las salidas disponibles
        queue<int> tempExit = exit; // Creamos una copia de la cola de salidas

        while (!tempExit.empty()) {
            int exitTimestamp = tempExit.front();
            tempExit.pop();

            // Calculamos la diferencia de tiempo (tiempo de horneado)
            if (exitTimestamp >= entryTimestamp) {
                int tiempo = exitTimestamp - entryTimestamp;
                tiempos[tiempo]++;  // Aumentamos el contador para esta diferencia
            }
        }
    }

    // Ahora buscamos el tiempo de horneado con la mayor frecuencia
    int maxFrecuencia = 0;
    int tiempoMaximo = -1;

    for (const auto& par : tiempos) {
        if (par.second > maxFrecuencia || (par.second == maxFrecuencia && par.first < tiempoMaximo)) {
            maxFrecuencia = par.second;
            tiempoMaximo = par.first;
        }
    }

    return tiempoMaximo;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        queue<int> entry, exit;

        // Leer los tiempos de entrada
        for (int i = 0; i < n; i++) {
            int valor;
            cin >> valor;
            entry.push(valor);
        }

        // Leer los tiempos de salida
        for (int i = 0; i < m; i++) {
            int valor;
            cin >> valor;
            exit.push(valor);
        }

        // Llamar a la función para obtener el tiempo de horneado más frecuente
        cout << tiempoHorneo(entry, exit) << endl;
    }

    return 0;
}