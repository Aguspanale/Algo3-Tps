#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

vector<vector<int>> memo;
vector<set<int>> pasadizos;
int maximo; 
int minimo;
int fortalezas;
int cantidad_pasadizos;
int inf = 1e9;

int camino_minimo_desde_n_con_k_pasadizos_restantes(int n, int k){
    if(memo[n][k] == -1){
        if (n == 0) {
            memo[n][k] = 1;
        }
        else{
            int minimo_no_uso_puente = 1 + camino_minimo_desde_n_con_k_pasadizos_restantes(n-1,k);
            int minimo_usando_puente = inf;
            if(k > 0){
                for (int vecino : pasadizos[n])
                {   
                    int aux =  2 + camino_minimo_desde_n_con_k_pasadizos_restantes(vecino,k-1);
                    minimo_usando_puente = min(minimo_usando_puente, aux);
                }
            }
            memo[n][k] = min(minimo_no_uso_puente, minimo_usando_puente);
        }
    }
    return memo[n][k];
}

int main() {
   int case_tests;
   cin >> case_tests;
   for (int i = 0; i < case_tests; i++)
   {
      cin >> fortalezas >> cantidad_pasadizos;
      pasadizos = vector<set<int>>(fortalezas, set<int>());
      memo = vector<vector<int>>(fortalezas, vector<int>(4,-1));
        for (int j = 0; j < cantidad_pasadizos; j++){
            int entrada, salida;
            cin >> entrada >> salida;
            entrada -= 1;
            salida -= 1;
            if (entrada < salida){ //Guardamos a partir de una muralla hacia donde podemos ir para atras, no nos importa desde el inicio al final.
                pasadizos[salida].insert(entrada);
            }
            else{
                pasadizos[entrada].insert(salida);
            }
        }
        cout << camino_minimo_desde_n_con_k_pasadizos_restantes(fortalezas - 1, 3) << endl;
   }   

   return 0;
}