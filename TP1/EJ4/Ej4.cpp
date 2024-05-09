#include <iostream>
#include <vector>
using namespace std;
long INF = 1e9;

vector<long> puestos;
vector<vector<long> > memoria; // k vectores de i posiciones posibles


long costoEntre(int primeraProve,int ultimaProve){
    long res = 0;
    if(primeraProve < 0){
        for (int i = 0; i < ultimaProve; ++i) {
            res += abs(puestos[i]-puestos[ultimaProve]);
        }
    } else if(ultimaProve >= puestos.size()){
        for (int i = primeraProve; i < puestos.size(); ++i) {
            res += abs(puestos[i]-puestos[primeraProve]);
        }
    } else {
        for (int i = primeraProve; i < ultimaProve; ++i) {
            res += min(abs(puestos[i]-puestos[ultimaProve]),abs(puestos[i]-puestos[primeraProve]));
        }
    }
    return res;
}

long costoMinimoDesde(int i, int k){
    if(memoria[k][i] != -1){
        return memoria[k][i];
    }
    long costoDeterminado = 0;
    if(k == 0){
        costoDeterminado = costoEntre(i,INF);
        memoria[k][i] = costoDeterminado;
        return costoDeterminado;
    } else {
        long minimo = INF;
        for (int j = i+1; j <= puestos.size() - k; ++j) {
            costoDeterminado = costoEntre(i,j);
            minimo = min(minimo,costoDeterminado + costoMinimoDesde(j,k-1));
        }
        memoria[k][i] = minimo;
        return minimo;
    }
}
void imprimirSecuencia(long mejorCosto){
    int indiceAnterior = -INF;
    int indiceActual = 0;
    long costoDeterminado;
    long costoEstaOpcion;
    for (int i = memoria.size()-1; i >= 0 ; --i) {
        while(true){
            costoDeterminado = costoEntre(indiceAnterior,indiceActual);
            costoEstaOpcion = costoDeterminado + memoria[i][indiceActual];
            if(costoEstaOpcion == mejorCosto){
                mejorCosto -= costoDeterminado;
                break;
            }
            indiceActual++;
        }
        indiceAnterior = indiceActual;
        cout << puestos[indiceActual] << " ";
        indiceActual++;
    }

}


int main() {
    int test_cases;
    cin >> test_cases;
    int k, n;
    for (int i = 0; i < test_cases; ++i) {
        memoria = vector<vector<long> >();
        puestos = vector<long>();
        cin >> n >> k;
        puestos.reserve(n);
        memoria.reserve(k+1);
        long in;
        vector<long> menosunos;
        for (int j = 0; j < n; ++j) {
            cin >> in;
            puestos.push_back(in);
        }

        menosunos = vector<long>(n,-1);
        for (int j = 0; j < k; ++j) {
            memoria.push_back(menosunos);
        }
        long costoDeterminado = 0;
        long mejorCosto = INF;
        long costoEstaOpcion;
        for (int j = 0; j <= puestos.size() - k; ++j) {
            costoDeterminado = costoEntre(-INF,j);
            costoEstaOpcion = costoDeterminado + costoMinimoDesde(j,k-1);
            mejorCosto = min(mejorCosto,costoEstaOpcion);
        }

        cout << mejorCosto << endl;
        imprimirSecuencia(mejorCosto);
        cout << endl;

    }
    return 0;
}
