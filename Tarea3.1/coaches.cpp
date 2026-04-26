/*
 Nicolas Zapata Clavijo
 8984273
 A-Problem A
 */

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

class Persona {
public:
    string nombre;
    int anioNacimiento;
    Persona()
    {
        nombre = "";
        anioNacimiento = 0;
    }
    Persona(string &nom, int anio)
    {
        nombre = nom;
        anioNacimiento = anio;
    }
};

void asignarGeneracionesBFS(const vector<vector<int>> &entrenadosPor, vector<int> &generacion) {
    queue<int> cola;
    int totalPersonas = generacion.size();
    for (int i = 0; i < totalPersonas; i++) {
        if (generacion[i] == 0) {
            cola.push(i);
        }
    }
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        int nuevaGeneracion = generacion[actual] + 1;
        for (int i = 0; i < (int)entrenadosPor[actual].size(); i++) {
            int hijo = entrenadosPor[actual][i];
            if (nuevaGeneracion > generacion[hijo]) {
                generacion[hijo] = nuevaGeneracion;
                cola.push(hijo);
            }
        }
    }
}

int seleccionarMejorCoachDelGrupo(const vector<int> &grupo, const vector<int> &cantidadEntrenados, const vector<Persona> &personas) {
    int idMejor = grupo[0];
    for (int i = 1; i < (int)grupo.size(); i++) {
        int idActual = grupo[i];
        if (cantidadEntrenados[idActual] > cantidadEntrenados[idMejor] ||
           (cantidadEntrenados[idActual] == cantidadEntrenados[idMejor] &&
            personas[idActual].anioNacimiento < personas[idMejor].anioNacimiento) ||
           (cantidadEntrenados[idActual] == cantidadEntrenados[idMejor] &&
            personas[idActual].anioNacimiento == personas[idMejor].anioNacimiento &&
            personas[idActual].nombre < personas[idMejor].nombre)) {
            idMejor = idActual;
        }
    }
    return idMejor;
}

int main() {
    int numCasos;
    cin >> numCasos;
    for (int caso = 1; caso <= numCasos; caso++) {
        int numPersonas, numRelaciones;
        cin >> numPersonas >> numRelaciones;
        vector<Persona> personas(numPersonas);
        unordered_map<string, int> diccionario;
        for (int i = 0; i < numPersonas; i++) {
            string nombre;
            int anio;
            cin >> nombre >> anio;
            personas[i] = Persona(nombre, anio);
            diccionario[nombre] = i;
        }
        vector<vector<int> > entrenadosPor(numPersonas);
        vector<int> cantidadEntrenados(numPersonas, 0);
        vector<bool> entrenado(numPersonas, false);
        for (int i = 0; i < numRelaciones; i++) {
            string entrenadorStr, jugadorStr;
            cin >> entrenadorStr >> jugadorStr;
            int idEntrenador = diccionario[entrenadorStr];
            int idJugador = diccionario[jugadorStr];
            cantidadEntrenados[idEntrenador]++;
            entrenado[idJugador] = true;
            entrenadosPor[idEntrenador].push_back(idJugador);
        }
        vector<int> generacion(numPersonas, -1);
        for (int i = 0; i < numPersonas; i++) {
            if (!entrenado[i])
                generacion[i] = 0;
        }
        asignarGeneracionesBFS(entrenadosPor, generacion);
        int generacionMax = -1;
        for (int i = 0; i < numPersonas; i++) {
            if (cantidadEntrenados[i] > 0 && generacion[i] > generacionMax)
                generacionMax = generacion[i];
        }
        vector<vector<int> > grupos(generacionMax + 1);
        for (int i = 0; i < numPersonas; i++) {
            if (cantidadEntrenados[i] > 0 && generacion[i] >= 0) {
                int gen = generacion[i];
                grupos[gen].push_back(i);
            }
        }
        cout << "Scenario #" << caso << ":\n";
        for (int gen = 0; gen <= generacionMax; gen++) {
            if (grupos[gen].empty())
                continue;
            int idMejor = seleccionarMejorCoachDelGrupo(grupos[gen], cantidadEntrenados, personas);
            cout << "Generation " << gen << ": " << personas[idMejor].nombre << "\n";
        }
        if (caso < numCasos)
            cout << "\n";
    }
    return 0;
}