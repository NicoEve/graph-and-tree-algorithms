/*
B-Problem B
Nicolás Zapata Clavijo
8984273
*/
/*
Tenemos que cada celda tiene 4 posibles orientaciones de la puerta, lo que basicamente sería
4 * n * m, donde en terminos de O sería O(n * m), y uso una priority_queue que tiene costo O(log n) por
operación de push o pop, como se hacen O(n * m) relajaciones entonces el costo total de mi codigo
sería O(n * m * log(n * m))
*/
#include <vector>
#include <climits>
#include <queue>
#include <iostream>
#include <string>

using namespace std;

int inf = INT_MAX;

int direccionInicial(char c)
{
    int dir = 0;
    if (c == 'W')
    {
        dir = 1;
    }
    else
    {
        if (c == 'S')
        {
            dir = 2;
        }
        else
        {
            if (c == 'E')
            {
                dir = 3;
            }
        }
    }
    return dir;
}

bool esPuerta(char c)
{
    bool puerta = false;
    if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
    {
        puerta = true;
    }
    return puerta;
}

struct Nodo
{
    int t, x, y, r;
    Nodo(int _t, int _x, int _y, int _r)
    {
        t = _t;
        x = _x;
        y = _y;
        r = _r;
    }
    bool operator<(const Nodo &o) const
    {
        return t > o.t;
    }
};

int calcularDistancia(vector<string> &grid, vector<int> &tiempos, int n, int m)
{
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(4, inf)));
    priority_queue<Nodo> pq;
    dist[n-1][0][0] = 0;
    pq.emplace(0, n-1, 0, 0);
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};
    vector<vector<int>> idx(n, vector<int>(m, -1));
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if (esPuerta(grid[i][j]))
            {
                idx[i][j] = cnt;
                cnt++;
            }
        }
    }
    while (!pq.empty())
    {
        Nodo cur = pq.top();
        pq.pop();
        int t = cur.t;
        int x = cur.x;
        int y = cur.y;
        int r = cur.r;
        if (t == dist[x][y][r])
        {
            if (esPuerta(grid[x][y]))
            {
                int id    = idx[x][y];
                int costo = tiempos[id];
                int r1    = (r + 1) % 4;
                int r2    = (r + 3) % 4;
                int nt   = t + costo;
                if (nt < dist[x][y][r1])
                {
                    dist[x][y][r1] = nt;
                    pq.emplace(nt, x, y, r1);
                }
                if (nt < dist[x][y][r2])
                {
                    dist[x][y][r2] = nt;
                    pq.emplace(nt, x, y, r2);
                }
            }
            for(int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] != '#')
                {
                    if (!esPuerta(grid[x][y]) || r == i)
                    {
                        int nr = 0;
                        if (esPuerta(grid[nx][ny]))
                        {
                            nr = direccionInicial(grid[nx][ny]);
                        }
                        int entrada = (i + 2) % 4;
                        if (!esPuerta(grid[nx][ny]) || entrada == nr)
                        {
                            int nt2 = t + 1;
                            if (nt2 < dist[nx][ny][nr])
                            {
                                dist[nx][ny][nr] = nt2;
                                pq.emplace(nt2, nx, ny, nr);
                            }
                        }
                    }
                }
            }

        }
    }
    int mejor = inf;
    for(int i = 0; i < 4; i++)
    {
        if (dist[0][m-1][i] < mejor)
        {
            mejor = dist[0][m-1][i];
        }
    }
    int resultado = mejor;
    if (resultado == inf)
    {
        resultado = -1;
    }
    return resultado;
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int n, m;
        cin >> n >> m;
        vector<string> grid(n);
        int puertas = 0;
        for(int i = 0; i < n; i++)
        {
            cin >> grid[i];
            for(int j = 0; j < m; j++)
            {
                if (grid[i][j] == 'N' || grid[i][j] == 'E' ||
                    grid[i][j] == 'S' || grid[i][j] == 'W')
                {
                    puertas++;
                }
            }
        }
        vector<int> tiempos(puertas);
        for(int i = 0; i < puertas; i++)
        {
            cin >> tiempos[i];
        }
        int res = calcularDistancia(grid, tiempos, n, m);
        if (res < 0)
        {
            cout << "Poor Kianoosh" << endl;
        }
        else
        {
            cout << res << endl;
        }
    }
    return 0;
}