#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
double C;
double epsilon = 0.005;
double cota_superior;

class DSU{
    public:
        vector<int> padre_componente;
        vector<int> tamano_componente;
        DSU(int cantidad){
            tamano_componente = vector<int>(cantidad,1);
            for(int i = 0; i < cantidad; i++){
                padre_componente.push_back(i);
            }
        }
        int find_set(int vert1){
            int vertex = vert1;
            while(padre_componente[vertex] != vertex){
                vertex = padre_componente[vertex];
            }
            return vertex;
        }        
        void unite(int vert1, int vert2){
            //weighted-union heuristic del cormen
            int padre_componente_vert1 = this->find_set(vert1);
            int padre_componente_vert2 = this->find_set(vert2);
            if (tamano_componente[padre_componente_vert1] < tamano_componente[padre_componente_vert2]) {
                padre_componente[padre_componente_vert1] = padre_componente_vert2;
                tamano_componente[padre_componente_vert2] += tamano_componente[padre_componente_vert1];
            } else {
                padre_componente[padre_componente_vert2] = padre_componente_vert1;
                tamano_componente[padre_componente_vert1] += tamano_componente[padre_componente_vert2];
            }
        }
        bool same_component(int vert1, int vert2){
            return this->find_set(vert1) == this->find_set(vert2);
        }
};

struct cable {
    int edificio1;
    int edificio2;
    int distancia;
    int repetidores;
};

bool operator<(const cable &c1, const cable &c2) {
    double r1 = c1.distancia - c1.repetidores * C;
    double r2 = c2.distancia - c2.repetidores * C;
    return r1 > r2;
}

pair<bool,pair<int,int>> hayArbol(double C,int N,vector<cable>& aristas){
    // hacer kruskal con peso = d - r * c y devolver si el peso total queda mayor q c
    sort(aristas.begin(), aristas.end());
    int agregados = 0;
    double sumaActual = 0;
    long long D = 0;
    long long R = 0;
    DSU dsu(N);
    while(agregados < N-1){ // queda aprox mlogm
        for(cable una_arista : aristas){
            if(dsu.find_set(una_arista.edificio1) != dsu.find_set(una_arista.edificio2)){
                dsu.unite(una_arista.edificio1,una_arista.edificio2);
                sumaActual += una_arista.distancia - una_arista.repetidores * C;
                D+= una_arista.distancia;
                R+= una_arista.repetidores;
                agregados += 1;
            }
            if (agregados == N-1){
                break;
            }
        }
    }
    return {sumaActual > 0,{D,R}};
}

void buscarDyR(int N, vector<cable>& aristas){ // busqueda binaria de C
    double superior = cota_superior;
    double inferior = 0; // limites superior e inferior para C
    pair<bool,pair<int,int>> infoArbol;
    while(superior - inferior > epsilon){
        C = (superior + inferior) / 2;
        infoArbol = hayArbol(C,N,aristas);
        if(infoArbol.first){
            inferior = C;
        } else {
            superior = C;
        }
    }
    infoArbol = hayArbol(C,N,aristas);
    cout << infoArbol.second.first << " " << infoArbol.second.second <<endl;
}

int main() {
    int test_cases, N, M;
    cin >> test_cases;
    for (int i = 0; i < test_cases; ++i) {
        cin >> N >> M;
        vector<cable> aristas;
        int u, v, d, r;
        for (int j = 0; j < M; ++j) {
            cin >> u >> v >> d >> r;
            u--;
            v--;
            cota_superior += d;
            aristas.push_back({u,v,d,r});
        }
        buscarDyR(N,aristas);
    }
    return 0;
}