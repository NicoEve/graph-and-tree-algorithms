/*
Algoritmo para Componentes Conexos mediante DFS
Autor: Carlos Ramirez
Fecha: Marzo 8 de 2025

 */

#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int n;
vector<vector<int> > adj(50000);
vector<vector<int> > comps;
bool visitado[50000];

void ccDFSAux(int v){
  int w;
  visitado[v] = true;
  comps[comps.size() - 1].push_back(v);
  
  for(int i = 0; i < adj[v].size(); i++){
    w = adj[v][i];
    if(!visitado[w])
      ccDFSAux(w);
  }
}

void ccDFS(){
  int i;
  
  for(i = 0; i < n; i++)
    visitado[i] = false;

  for(i = 0; i < n; i++){
    if(!visitado[i]){
      comps.push_back(vector<int>());
      ccDFSAux(i);
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
  
  ccDFS();

  cout << "Total Componentes: " << comps.size() << endl;
  for(i = 0; i < comps.size(); i++){
    cout << "Componente " << i + 1 << ":";
    for(j = 0; j < comps[i].size(); j++)
      cout << " " << comps[i][j];
    cout << endl;
  }
  
  return 0;
}
