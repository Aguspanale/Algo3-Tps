#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

vector<list<int>> grafo;
vector<vector<int>> capacidad;
int INF = 1e9;

struct arista{
    int fila;
    int columna;
};

struct aristaPesada{
    aristaPesada(int n,int p):nodo(n),peso(p){};
    int nodo;
    int peso;
};

void aristas_columnas(int N, vector<vector<int>> &tablero, vector<vector<arista>> &nodos_por_casilla, int& cantidad_de_nodos) {
    for (int k = 0; k < N; ++k) {
        bool anterior_roto = true;
        for (int j = 0; j < N; ++j) {
            if (tablero[j][k] == 0 && anterior_roto){
                cantidad_de_nodos++;
                nodos_por_casilla[j][k].columna = cantidad_de_nodos;
                anterior_roto = false;
            } else if(tablero[j][k] == 0){
                nodos_por_casilla[j][k].columna = cantidad_de_nodos;
            } else {
                anterior_roto = true;
            }

        }
    }
}

void aristas_filas_y_input(int N, vector<vector<int>> &tablero, vector<vector<arista>> &nodos_por_casilla, int& cantidad_de_nodos) {
    for (int j = 0; j < N; ++j) {
        bool anterior_roto = true;
        for (int k = 0; k < N; ++k) {
            cin >> tablero[j][k];
            if (tablero[j][k] == 0 && anterior_roto){
                cantidad_de_nodos++;
                nodos_por_casilla[j][k].fila = cantidad_de_nodos;
                anterior_roto = false;
            } else if(tablero[j][k] == 0){
                nodos_por_casilla[j][k].fila = cantidad_de_nodos;
            } else {
                anterior_roto = true;
            }

        }
    }
}


int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : grafo[cur]) {
            if (parent[next] == -1 && capacidad[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacidad[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}


//copiado de cpalgorithms

int maxflow(int s, int t,int cantidad_nodos) {
    int flow = 0;
    vector<int> parent(cantidad_nodos);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacidad[prev][cur] -= new_flow;
            capacidad[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    int test_cases;
    cin >> test_cases;
    for (int i = 0; i < test_cases; ++i) {
        int N;
        cin >> N;
        vector<vector<int>> tablero(N,vector<int>(N,0));
        vector<vector<arista>> nodos_por_casilla(N,vector<arista>(N,{-1,-1}));
        int cantidad_de_nodos = 0;

        aristas_filas_y_input(N, tablero, nodos_por_casilla, cantidad_de_nodos);
        int nodos_fila = cantidad_de_nodos;
        aristas_columnas(N, tablero, nodos_por_casilla, cantidad_de_nodos);
        grafo = vector<list<int>> (cantidad_de_nodos + 3,list<int>());
        capacidad = vector<vector<int>> (cantidad_de_nodos + 3,vector<int>(cantidad_de_nodos + 3,0));
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                if(!tablero[k][j]){
                    grafo[nodos_por_casilla[k][j].fila].push_front(nodos_por_casilla[k][j].columna);
                    grafo[nodos_por_casilla[k][j].columna].push_front(nodos_por_casilla[k][j].fila);
                    capacidad[nodos_por_casilla[k][j].fila][nodos_por_casilla[k][j].columna] = 1;
                }
            }
        }
        for (int j = 1; j < nodos_fila + 1; ++j) {
            grafo[cantidad_de_nodos + 1].push_front(j);
            grafo[j].push_front(cantidad_de_nodos + 1);
            capacidad[cantidad_de_nodos + 1][j] = 1;
        }
        for (int j = nodos_fila + 1; j < cantidad_de_nodos + 1; ++j) {
            grafo[j].push_front(cantidad_de_nodos+2);
            grafo[cantidad_de_nodos + 2].push_front(j);
            capacidad[j][cantidad_de_nodos+2] = 1;
        }
        for (int j = 0; j < cantidad_de_nodos + 3; j++)
        {
            capacidad[j][j] = INF;
        }
        
        cout << maxflow(cantidad_de_nodos+1,cantidad_de_nodos+2,cantidad_de_nodos+3) << endl;
    }

    return 0;
}