//
// Created by Nicolas on 3/03/2025.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

vector<vector<int>> movimientos = {{1, 0, 0, 0}, {-1, 0, 0, 0},{0, 1, 0, 0}, {0, -1, 0, 0},{0, 0, 1, 0}, {0, 0, -1, 0},{0, 0, 0, 1},
    {0, 0, 0, -1} };

int convertirNumero(vector<int> &numero)
{
    int numeroFinal = numero[0] * 1000 + numero[1] * 100 + numero[2] * 10 + numero[3];
    return numeroFinal;
}

vector<int> convertirVector(int numero)
{
    vector<int> digitos = {(numero / 1000) % 10, (numero / 100) % 10, (numero / 10) % 10, numero % 10};
    return digitos;
}

int minimosMovimientos(vector<int> &numeroInicial, int numeroLlegada, unordered_set<int> &numerosProhibidos)
{
    int pasosTotales = -1, numeroInicio = convertirNumero(numeroInicial);
    bool ans = false;
    queue<pair<int, int>> q;
    unordered_set<int> vis;
    q.emplace(numeroInicio, 0);
    vis.insert(numeroInicio);
    if (numeroInicio == numeroLlegada)
    {
        ans = true;
        pasosTotales = 0;
    }
    if (numerosProhibidos.find(numeroInicio) != numerosProhibidos.end())
    {
        ans = true;
    }
    while (!q.empty() && !ans)
    {
        pair<int, int> nodo = q.front();
        q.pop();
        int actual = nodo.first;
        int pasos = nodo.second;
        vector<int> estadoActual = convertirVector(actual);
        for (int i = 0; i < 8; i++)
        {
            vector<int> nuevoEstado = estadoActual;
            for (int j = 0; j < 4; j++)
            {
                nuevoEstado[j] = (nuevoEstado[j] + movimientos[i][j] + 10) % 10;
            }
            int estado = convertirNumero(nuevoEstado);
            if (numerosProhibidos.find(estado) == numerosProhibidos.end())
            {
                if (estado == numeroLlegada)
                {
                    pasosTotales = pasos + 1;
                    ans = true;
                }
                if (vis.find(estado) == vis.end())
                {
                    vis.insert(estado);
                    q.emplace(estado, pasos + 1);
                }
            }
        }
    }
    return pasosTotales;
}

int main()
{
    int N;
    cin >> N;
    while (N--)
    {
        vector<int> numeroInicial(4);
        for (int i = 0; i < 4; i++)
        {
            cin >> numeroInicial[i];
        }
        int numeroLlegada = 0, digito;
        for (int i = 0; i < 4; i++)
        {
            cin >> digito;
            numeroLlegada = numeroLlegada * 10 + digito;
        }
        int cantidadProhibidos;
        cin >> cantidadProhibidos;
        unordered_set<int> numerosProhibidos;
        for (int i = 0; i < cantidadProhibidos; i++) {
            vector<int> numeroProhibido(4);
            for (int j = 0; j < 4; j++) {
                cin >> numeroProhibido[j];
            }
            numerosProhibidos.insert(convertirNumero(numeroProhibido));
        }
        if (N > 0)
        {
            cin.ignore();
        }
        cout << minimosMovimientos(numeroInicial, numeroLlegada, numerosProhibidos) << endl;
    }
    return 0;
}