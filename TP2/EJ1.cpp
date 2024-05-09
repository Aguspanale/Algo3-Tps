#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> lista_adyacencia;
vector<int> estado_dfs; // 0 WHITE 1 GRAY 2 BLACK
vector<pair<int,int>> lista_aristas;
vector<int> back_edges_con_extremo_inferior; 
vector<int> back_edges_con_extremo_superior;
pair<int,int> removido_actual;
int cantidad_bases;
int cantidad_enlaces;
vector<vector<int>> tree_edges;
vector<pair<int,int>> importantes;
vector<int> memo;

bool es_misma_arista(int vertice, int vertice_hijo, pair<int,int> &b){
    return (vertice_hijo == b.first && vertice == b.second) || (vertice == b.first && vertice_hijo == b.second);
}

void DFS(int vertice, int padre){
    estado_dfs[vertice] = 1;
    for(int vertice_hijo : lista_adyacencia[vertice]){
        if(!es_misma_arista(vertice,vertice_hijo, removido_actual)){
            if (estado_dfs[vertice_hijo] == 0){
                tree_edges[vertice].push_back(vertice_hijo);
                DFS(vertice_hijo, vertice);
            } 
            else if (vertice_hijo != padre && estado_dfs[vertice_hijo] != 2){
                back_edges_con_extremo_inferior[vertice]++;
                back_edges_con_extremo_superior[vertice_hijo]++;
            }
        }
    }
    estado_dfs[vertice] = 2;
}

int cantidad_cubren_arista(int vert){
    if (memo[vert] != -1) {
        return memo[vert];
    }
    int res = 0;
    for (int hijo : tree_edges[vert]) {
        res += cantidad_cubren_arista(hijo);
    }
    res -= back_edges_con_extremo_superior[vert];
    res += back_edges_con_extremo_inferior[vert];
    memo[vert] = res;
    return res;
}

bool es_puente(int hijo){
    return cantidad_cubren_arista(hijo) == 0;  
}

bool encontrar_puentes(){
    DFS(0,-1);
    for (int vertice = 0; vertice < cantidad_bases; vertice++)
    {
        if(vertice != 0 && es_puente(vertice) ){
            return true;
        }
    }
    return false;
}

void encontrar_importantes(){
    importantes = vector<pair<int,int>>();
    for(pair<int,int> arista_a_remover : lista_aristas){

        tree_edges = vector<vector<int>>(cantidad_bases, vector<int>());
        back_edges_con_extremo_inferior = vector<int>(cantidad_bases,0);
        back_edges_con_extremo_superior = vector<int>(cantidad_bases,0);
        memo = vector<int>(cantidad_bases,-1);
        estado_dfs = vector<int>(cantidad_bases,0);

        removido_actual = arista_a_remover;
        if(encontrar_puentes()){
            importantes.push_back(removido_actual);
        }
    }
}

int main(){
    int case_test;
    cin >> case_test;
    for (int i = 0; i < case_test; i++){

        cin >> cantidad_bases >> cantidad_enlaces;
        lista_adyacencia = vector<vector<int>>();
        lista_aristas = vector<pair<int,int>>();

        for (int j = 0; j < cantidad_bases; j++)
        {
            lista_adyacencia.push_back(vector<int>());
        }
        
        for (int j = 0; j < cantidad_enlaces; j++)
        {
            int vertice1,vertice2;
            cin >> vertice1 >> vertice2;
            lista_adyacencia[vertice1].push_back(vertice2);
            lista_adyacencia[vertice2].push_back(vertice1);
            lista_aristas.push_back(make_pair(vertice1,vertice2));
        }

        encontrar_importantes();
        cout << importantes.size() << endl; 
        for (pair<int,int> importante : importantes)
        {
            cout << importante.first << ' ' << importante.second << endl;
        }
    }

    return 0;
}