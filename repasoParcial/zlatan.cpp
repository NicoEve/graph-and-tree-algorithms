/*
Nicolas Zapata Clavijo
8984273
E-Problem E
*/

/*
Para este algoritmo estoy varios algoritmos, kosaraju que tiene complejidad O(n + m) siendo n
el numero de ciudad del impero y m la cantidad de caminos, un floyd-warshall con complejidad
O(d^3) donde d va a ser la cantidad de ciudades que haya en un esto y como tal la
complejidad final de este sería O(e(d^3)) donde como dije d es el número de ciudad que hay en cada estado
y e sería el numero total de estados ya que hago un floyd por cada estado , el calculo del centro que tiene
complejidad O(e) que e es el número de estados y esto se debe a que llamamos centro con el grafo de componentes
entonces la complejidad va a ser igual al número de componente que haya en el grafo y por ultimo un dijkstra con
complejidad O((n + m) * log n) donde n y m siguen teniendo los significados anteriores ya que este se llama con el grafo
original, la complejidad que predomina es O(e(d^3)) por ende esa es la complejidad final de mi codigo.
*/

#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_set>

using namespace std;

void kosarajuAux(vector<vector<pair<int, int>>>&, vector<bool>&, list<int>&, int);
void asignar(vector<vector<pair<int, int>>>&, vector<int>&, int, int);
vector<vector<int>> floydWarshall(vector<vector<int>>&);
pair<int, int> excentricity;
int inf = INT_MAX;

struct pairHash {
    int operator()(const pair<int, int>& p) const {
        int h1 = p.first;
        int h2 = p.second;
        return h1 ^ (h2 << 1);
    }
};

vector<int> kosaraju(vector<vector<pair<int, int>>> &adj, vector<vector<pair<int, int>>> &adjT)
{
    int num = 0;
    vector<bool> visitados(adj.size(), false);
    vector<int> sccInd(adj.size(), -1);
    list<int> ord;
    for(int i = 0; i < adj.size(); i++)
        if(!visitados[i]) kosarajuAux(adj, visitados, ord, i);
    for(list<int>::iterator it = ord.begin(); it != ord.end(); it++)
    {
        if(sccInd[*it] == -1)
        {
            asignar(adjT, sccInd, *it, num++);
        }
    }
    return sccInd;
}

void kosarajuAux(vector<vector<pair<int, int>>> &adj, vector<bool> &visitados, list<int> &ord, int v)
{
    visitados[v] = true;
    for(int i = 0; i < adj[v].size(); i++)
        if(!visitados[adj[v][i].first])
            kosarajuAux(adj, visitados, ord, adj[v][i].first);
    ord.push_front(v);
}

void asignar(vector<vector<pair<int, int>>> &adjT, vector<int> &sccInd, int u, int num)
{
    sccInd[u] = num;
    for(int i = 0; i < adjT[u].size(); i++)
    {
        if(sccInd[adjT[u][i].first] == -1)
            asignar(adjT, sccInd, adjT[u][i].first, num);
    }
}

vector<vector<int>> floydWarshall(vector<vector<int>> &adj)
{
    vector<vector<int>> d(adj.size(), vector<int>(adj.size(), inf));
    for(int i = 0; i < adj.size(); i++)
    {
        for(int j = 0; j < adj.size(); j++)
            d[i][j] = adj[i][j];
    }
    for(int i = 0; i < adj.size(); i++)
        d[i][i] = 0;
    for(int k = 0; k < adj.size(); k++)
    {
        for(int i = 0; i < adj.size(); i++)
        {
            for(int j = 0; j < adj.size(); j++)
                if(d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];

        }
    }
    return d;
}

unordered_set<int> center(vector<vector<int>> &adj)
{
    int nivelMax = 0;
    vector<int> nivel(adj.size(), 0);
    vector<int> grado(adj.size());
    for(int i = 0; i < adj.size(); i++)
        grado[i] = adj[i].size();
    queue<int> q;
    unordered_set<int> nodosCentro;
    for(int i = 0; i < adj.size(); i++)
    {
        if(grado[i] == 1)
            q.push(i);
    }
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        for(int w = 0; w < adj[v].size(); w++)
        {
            grado[adj[v][w]] --;
            if(grado[adj[v][w]] == 1)
            {
                q.push(adj[v][w]);
                nivel[adj[v][w]] += nivel[v] + 1;
                nivelMax = max(nivelMax, nivel[adj[v][w]]);
            }
        }
    }
    for(int i = 0; i < adj.size(); i++)
    {
        if(nivel[i] == nivelMax)
            nodosCentro.insert(i);
    }
    return nodosCentro;
}

vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int s)
{
    vector<int> dist(adj.size(), inf);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.emplace(dist[s], s);
    while(!q.empty())
    {
        int du = q.top().first;
        int u = q.top().second;
        q.pop();
        if(dist[u] == du)
        {
            for(int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i].first;
                int duv = adj[u][i].second;
                if(du + duv < dist[v])
                {
                    dist[v] = du + duv;
                    q.emplace(dist[v], v);
                }
            }
        }
    }
    return dist;
}

pair<int, int> solve(vector<vector<pair<int, int>>> &adj, vector<vector<pair<int, int>>> &adjT, vector<vector<int>> &matriz)
{
    vector<int> capitalCities;
    vector<int> sccInd = kosaraju(adj, adjT);
    int numeroComponentes = 0;
    for(int i = 0; i < sccInd.size(); i++)
        numeroComponentes = max(numeroComponentes, sccInd[i]);
    numeroComponentes ++;
    vector<vector<int>> componentes(numeroComponentes);
    pair<int, int> ans;
    for(int i = 0; i < sccInd.size(); i++)
        componentes[sccInd[i]].push_back(i);
    for(int i = 0; i < numeroComponentes; i++)
    {
        int tamano = componentes[i].size();
        vector<vector<int>> subMatriz(tamano, vector<int>(tamano, inf));
        for(int j = 0; j < tamano; j++)
        {
            for(int k = 0; k < tamano; k++)
            {
                int u = componentes[i][j];
                int v = componentes[i][k];
                subMatriz[j][k] = matriz[u][v];
            }
        }
        vector<vector<int>> distancias = floydWarshall(subMatriz);
        int sumaMinima = inf, indiceNodo = 0;
        for(int j = 0; j < tamano; j++)
        {
            int sum = 0;
            for(int k = 0; k < tamano; k++)
            {
                if(distancias[j][k] != inf)
                    sum += distancias[j][k];
            }
            if(sum < sumaMinima || (sum == sumaMinima && componentes[i][j] < componentes[i][indiceNodo]))
            {
                sumaMinima = sum;
                indiceNodo = j;
            }
        }
        int nodo = componentes[i][indiceNodo];
        capitalCities.push_back(nodo);
    }
    vector<vector<pair<int, int>>> aux = adj;
    for(int i = 0; i < aux.size(); i++)
    {
        for(int j = 0; j < aux[i].size(); j++)
        {
            int v = aux[i][j].first;
            int d = aux[i][j].second * 2;
            if(sccInd[i] != sccInd[v])
            {
                bool existe = false;
                for(int k = 0; k < aux[v].size() && !existe; k++)
                {
                    if(aux[v][k].first == i)
                        existe = true;
                }
                if(!existe)
                    adj[v].emplace_back(i, d);
            }
        }
    }
    vector<vector<int>> grafoComponentes(numeroComponentes);
    unordered_set<pair<int, int>, pairHash> usados;
    for(int i = 0; i < adj.size(); i++)
    {
        for(int j = 0; j < adj[i].size(); j++)
        {
            int v = adj[i][j].first;
            if(sccInd[i] != sccInd[v])
            {
                int compU = sccInd[i];
                int compV = sccInd[v];
                pair<int, int> componente = {min(compU, compV), max(compU, compV)};
                if(usados.find(componente) == usados.end())
                {
                    grafoComponentes[compU].push_back(compV);
                    grafoComponentes[compV].push_back(compU);
                    usados.insert(componente);
                }
            }
        }
    }
    unordered_set<int> componente = center(grafoComponentes);
    int capital = 0;
    if(componente.size() == 1)
    {
        auto it = componente.begin();
        int u = *it;
        componente.erase(it);
        capital = capitalCities[u];
    }
    else
    {
        auto it = componente.begin();
        int u = *it;
        componente.erase(it);
        auto it2 = componente.begin();
        int v = *it2;
        if(capitalCities[u] < capitalCities[v])
            capital = capitalCities[u];
        else
            capital = capitalCities[v];
    }
    vector<int> distancias = dijkstra(adj, capital);
    int suma = 0;
    for(int i = 0; i < capitalCities.size(); i++) {
        if(capitalCities[i] != capital)
            suma += distancias[capitalCities[i]];
    }
    ans.first = capital;
    ans.second = suma;
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        pair<int, int> ans;
        cin >> n >> m;
        vector<vector<pair<int, int>>> adj(n);
        vector<vector<pair<int, int>>> adjT(n);
        vector<vector<int>> matriz(n, vector<int>(n, inf));
        for(int i = 0; i < m; i++)
        {
            int u, v, c;
            cin >> u >> v >> c;
            matriz[u][v] = c;
            adj[u].emplace_back(v, c);
            adjT[v].emplace_back(u, c);
        }
        ans = solve(adj,adjT, matriz);
        cout << ans.first << " " << ans.second << endl;
    }
    return 0;
}