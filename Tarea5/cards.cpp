/*
A-Problem A
Nicolás Zapata Clavijo
8984273
*/

/*
En este algoritmo basicamente ejecuto un dijkstra 2 veces por cada caso de prueba, tenemos que la complejidad de dijkstra es de O(m + n log n),
donde n es el número de nodos y m el número de aristas, al ejecutarlo dos veces quedaría O(2(m + n log n), sin embargo la constante 2 se ignora 
en la notación O por ende la complejidad de mi solución es O(m + n log n)
*/

#include <iostream>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

int inf = INT_MAX;

vector<int> dijkstra(vector<vector<pair<int, int>>> &G, int s)
{
    vector<int> dist(G.size(), inf);
    dist[s] = 0;
    vector<int> pred(G.size(), -1);
    priority_queue<pair<int, int>> pq;
    pq.emplace(dist[s], s);
    while (!pq.empty())
    {
        int du = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(dist[u] == du)
        {
            int v, duv;
            for(int i = 0; i < G[u].size(); i++)
            {
                v = G[u][i].first;
                duv = G[u][i].second;
                if(du + duv < dist[v])
                {
                    dist[v] = du + duv;
                    pred[v] = u;
                    pq.emplace(dist[v], v);
                }
            }
        }
    }
    return dist;
}

int main()
{
    int N;
    cin >> N;
    while(N--)
    {
        int p, q, u, v, w, ans = 0;
        cin >> p >> q;
        vector<vector<pair<int, int>>> G(p + 1);
        vector<vector<pair<int, int>>> GT(p + 1);
        for(int j = 0; j < q; j++)
        {
            cin >> u >> v >> w;
            G[u].emplace_back(v, w);
            GT[v].emplace_back(u, w);
        }
        vector<int> dist = dijkstra(G, 1);
        vector<int> distT = dijkstra(GT, 1);
        for(int j = 1; j <= p; j++)
        {
            ans += dist[j];
        }
        for(int j = 1; j <= p; j++)
        {
            ans += distT[j];
        }
        cout << ans << endl;
    }
    return 0;
}