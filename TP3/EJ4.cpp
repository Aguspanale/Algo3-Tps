#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
using namespace std;

int cantidad_esquinas;
int cantidad_calles;
int x;
int INF = 1e9;
int paquetes_por_persona;
vector<vector<int>> capacidad_aristas;
vector<vector<int>> referencia_capacidad_aristas;
typedef int capacidad;
typedef int vertice;
vector<list<int>> lista_adyacencia;

//copiado de cpalgorithms

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : lista_adyacencia[cur]) {
            if (parent[next] == -1 && referencia_capacidad_aristas[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, referencia_capacidad_aristas[cur][next]);
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
            referencia_capacidad_aristas[prev][cur] -= new_flow;
            referencia_capacidad_aristas[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}  

void actualizar_arista(){
    for (int i = 0; i < cantidad_esquinas; i++)
    {
        for (int j = 0; j < cantidad_esquinas; j++)
        {
            referencia_capacidad_aristas[i][j] = capacidad_aristas[i][j]/paquetes_por_persona;
        }
        
    }
    
} 

int busqueda_de_paquetes_maximo(){
    int limite_superior = 1e9; 
    int limite_inferior = 0;
    paquetes_por_persona = 1e9/2;

    while(limite_superior - limite_inferior != 1){
        actualizar_arista();
        int cantidad_personas = maxflow(0, cantidad_esquinas-1, cantidad_esquinas);
        if(cantidad_personas >= x){
            limite_inferior = paquetes_por_persona;
            paquetes_por_persona = (limite_superior + limite_inferior)/2; 
        }
        else{
            limite_superior = paquetes_por_persona;
            paquetes_por_persona = (limite_superior + limite_inferior)/2; 
        }
    }
    return limite_inferior;
}

int main() {
   int case_tests;
   cin >> case_tests;
   for (int i = 0; i < case_tests; i++)
   {
        cin >> cantidad_esquinas >> cantidad_calles >> x;
        capacidad_aristas = vector<vector<int>>(cantidad_esquinas,vector<int>(cantidad_esquinas,0));
        referencia_capacidad_aristas = vector<vector<int>>(cantidad_esquinas,vector<int>(cantidad_esquinas,0));
        lista_adyacencia = vector<list<int>>(cantidad_esquinas, list<int>());
        for (int j = 0; j < cantidad_calles; j++)
        {
            int vert1, vert2, capacidad;
            cin >> vert1 >> vert2 >> capacidad;
            lista_adyacencia[vert1 - 1].push_back(vert2-1);
            capacidad_aristas[vert1-1][vert2-1] = capacidad;
        }

        int paquetes_por_persona_max = busqueda_de_paquetes_maximo();
        cout << paquetes_por_persona_max * x << endl; 
   }   

   return 0;
}