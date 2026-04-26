/*
B-Problem B
Nicolas Zapata
8984273
*/

#include <vector>
#include <map>
#include <iostream>

using namespace std;

int tiempoHorneo(vector<int> entry, vector<int> exit)
{
    int valorMaximo = 0, claveMenor = 0, tiempoHorneo = 0, i = 0, j = 0;
    int timeStamp, entryTimestamp, exitTimestamp;
    bool flag = false;
    map<int, int> tiempos;
    for(i = 0; i < exit.size(); i++)
    {
        exitTimestamp = exit[i];
        flag = false;
        for(j = 0; j < entry.size() && !flag; j++)
        {
            entryTimestamp = entry[j];
            if(exitTimestamp < entryTimestamp)
            {
                flag = true;
            }
            else
            {
                timeStamp = exitTimestamp - entryTimestamp;
                tiempos[timeStamp] += 1;
            }
        }
    }
    for(map<int, int>::iterator it = tiempos.begin(); it != tiempos.end(); it++) {
        if(it->second > valorMaximo) {
            valorMaximo = it->second;
            claveMenor = it->first;
        }
        else if(it->second ==  valorMaximo && it->first < claveMenor)
        {
            claveMenor = it->first;
        }
        tiempoHorneo = claveMenor;
    }
    return tiempoHorneo;
}

int main()
{
    int n, m, resultado;
    while(cin >> n >> m)
    {
        vector<int> entry, exit;
        for(int i = 0; i < n; i++)
        {
            int valor;
            cin >> valor;
            entry.push_back(valor);
        }
        for(int i = 0; i < m; i++)
        {
            int valor;
            cin >> valor;
            exit.push_back(valor);
        }
        resultado = tiempoHorneo(entry, exit);
        cout << resultado << endl;
    }
    return 0;
}

/*
La complejidad de este codigo en el peor de los casos si el flag nunca se vuelve verdadero en el segundo ciclo
es O(n^2) ya que tenemos un ciclo anidado
*/