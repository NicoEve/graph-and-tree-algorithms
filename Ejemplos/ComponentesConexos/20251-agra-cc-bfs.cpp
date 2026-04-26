/*
Algoritmo para Componentes Conexos mediante BFS
Autor: Carlos Ramirez
Fecha: Marzo 8 de 2025

 */

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int n;
vector<vector<int> > adj(50000);
vector<vector<int> > comps;
bool visitado[50000];

void ccBFSAux(int v){
  int j, w, curr;
  queue<int> cola;
  
  comps[comps.size() - 1].push_back(v);
  cola.push(v);
  visitado[v] = true;

  while(!cola.empty()){
    curr = cola.front();
    cola.pop();

    for(j = 0; j < adj[curr].size(); j++){
      w = adj[curr][j];
      if(!visitado[w]){
	cola.push(w);
	visitado[w] = true;
	comps[comps.size() - 1].push_back(w);
      }
    }
  }
}

void ccBFS(){
  int i;
  
  for(i = 0; i < n; i++)
    visitado[i] = false;

  for(i = 0; i < n; i++){
    if(!visitado[i]){
      comps.push_back(vector<int>());
      ccBFSAux(i);
    }
  }
}

int main(){
  int m, i, j, aux1, aux2;

  cin >> n >> m;

  for(i = 0; i < m; i++){
    cin >> aux1 >> aux2;
    adj[aux1].push_back(aux2);
  }
  
  ccBFS();

  cout << "Total Componentes: " << comps.size() << endl;
  for(i = 0; i < comps.size(); i++){
    cout << "Componente " << i + 1 << ":";
    for(j = 0; j < comps[i].size(); j++)
      cout << " " << comps[i][j];
    cout << endl;
  }
  
  return 0;
}
