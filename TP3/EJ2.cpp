#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int INF = 1e9;

struct relacion{
    int nodo1;
    int nodo2;
    int latencia;
    bool operator<(const relacion otraRelacion) const{
        return this->latencia > otraRelacion.latencia;
    }
};

void recalcular_distancias(relacion actual, vector<vector<int>>& distancia, vector<vector<int>>& distancia_conexion){
    for (int i = 0; i < distancia.size(); ++i) {
        for (int j = 0; j < distancia.size(); ++j) {
            distancia[i][j] = min(min(distancia[i][actual.nodo1] + actual.latencia + distancia[actual.nodo2][j],distancia[i][actual.nodo2] + actual.latencia + distancia[actual.nodo1][j]),distancia[i][j]);
            distancia_conexion[i][j] = min(min(distancia_conexion[i][actual.nodo1] + 1 + distancia_conexion[actual.nodo2][j],distancia_conexion[i][actual.nodo2] + 1 + distancia_conexion[actual.nodo1][j]),distancia_conexion[i][j]);
        }
    }
}

bool reconstruir_grafo(vector<vector<int>>& latencia, vector<vector<int>>& distancia, priority_queue<relacion>& relaciones, vector<vector<int>>& distancia_conexion){
    while(!relaciones.empty()){
        relacion actual = relaciones.top();
        if(distancia[actual.nodo1][actual.nodo2] < actual.latencia){
            return false;
        } else if(distancia[actual.nodo1][actual.nodo2] > actual.latencia){
            recalcular_distancias(actual,distancia,distancia_conexion);
        }
        relaciones.pop();
    }
    return true;
}

int main() {
    int test_cases;
    cin >> test_cases;
    for (int i = 0; i < test_cases; ++i) {
        int N;
        cin >> N;
        vector<vector<int>> latencia(N,vector<int>(N,0));
        vector<vector<int>> distancia(N,vector<int>(N,INF));
        vector<vector<int>> distancia_conexion(N,vector<int>(N,INF));
        for (int j = 0; j < N; ++j) {
            distancia[j][j] = 0;
            distancia_conexion[j][j] = 0;
        }
        priority_queue<relacion> relaciones;
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < j; ++k) {
                cin >> latencia[j][k];
                latencia[k][j] = latencia[j][k];
                relaciones.push(relacion({j,k,latencia[j][k]}));
            }
        }
        bool posible = reconstruir_grafo(latencia,distancia,relaciones,distancia_conexion);
        if(posible){
            cout << "POSIBLE" << endl;
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    cout << distancia_conexion[j][k] << " ";
                }
                cout << endl;
            }
            cout << endl;
        } else { cout << "IMPOSIBLE" << endl;}
    }
    return 0;
}

