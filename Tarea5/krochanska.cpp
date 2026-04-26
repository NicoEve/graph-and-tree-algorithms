#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

vector<long long> dijkstra(vector<vector<pair<int,int>>> &adj, int start, int k){
    vector<long long> dist(k, INF);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while(!pq.empty()){
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(d <= dist[u]){
            for(auto &edge : adj[u]){
                int v = edge.first;
                int w = edge.second;
                if(d + w < dist[v]){
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    return dist;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        int n, s; cin >> n >> s;
        vector<vector<int>> lineas(s);
        vector<int> apariciones(n+1, 0);
        for(int i = 0; i < s; i++){
            int x;
            while(cin >> x && x != 0){
                lineas[i].push_back(x);
                apariciones[x]++;
            }
        }
        vector<int> importantes;
        for(int i = 1; i <= n; i++){
            if(apariciones[i] > 1){
                importantes.push_back(i);
            }
        }
        int k = importantes.size();
        unordered_map<int,int> indice;
        for(int i = 0; i < k; i++){
            indice[importantes[i]] = i;
        }
        vector<vector<pair<int,int>>> adj(k);
        for(auto &linea : lineas){
            int ultima = -1, distAcum = 0;
            for(int i = 0; i < linea.size(); i++){
                int est = linea[i];
                if(apariciones[est] > 1){
                    if(ultima != -1){
                        int u = indice[ultima];
                        int v = indice[est];
                        int costo = distAcum * 2;
                        adj[u].push_back({v, costo});
                        adj[v].push_back({u, costo});
                    }
                    ultima = est;
                    distAcum = 0;
                }
                if(i + 1 < linea.size()){
                    distAcum++;
                }
            }
        }
        int mejorEstacion = importantes[0];
        long long mejorSuma = INF;
        for(int i = 0; i < k; i++){
            vector<long long> dist = dijkstra(adj, i, k);
            
            long long suma = 0;
            for(int j = 0; j < k; j++){
                suma += dist[j];
                if(suma >= mejorSuma){
                    j = k;
                }
            }
            if(suma < mejorSuma || (suma == mejorSuma && importantes[i] < mejorEstacion)){
                mejorSuma = suma;
                mejorEstacion = importantes[i];
            }
        }
        cout << "Krochanska is in: " << mejorEstacion << "\n";
    }
}