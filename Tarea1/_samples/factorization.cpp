/*
D-Problem D
Nicolas Zapata
8984273
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void findFactors(int start, int current, int n, vector<int>& currentFactors, vector<vector<int>>& allFactors)
{
    if(current == n)
    {
        allFactors.push_back(currentFactors);
        return;
    }
    for(int i = start; i <= n / current; i++)
    {
        if (n % (current * i) == 0)
        {
            currentFactors.push_back(i);
            findFactors(i, current * i, n, currentFactors, allFactors);
            currentFactors.pop_back();
        }
    }
}

// Función para procesar cada número N
void processNumber(int n) {
    vector<vector<int>> allFactors;
    vector<int> currentFactors;
    findFactors(2, 1, n, currentFactors, allFactors);
    // Imprimir el número de factorizaciones
    cout << allFactors.size() << endl;
    // Imprimir cada factorización en orden no decreciente
    for(int i = 0; i < allFactors.size(); i++)
    {
        for(int j = 0; j < allFactors[i].size(); j++)
        {
            cout << allFactors[i][j];
            if (j != allFactors[i].size() - 1) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    // Leer números hasta que N sea 0
    while (cin >> n && n != 0)
    {
        processNumber(n);
    }
    return 0;
}

/*
La complejidad del codigo es de O(n^3) debido a que hay 3 ciclos anidados en la función main que llama a la
recursiva
*/