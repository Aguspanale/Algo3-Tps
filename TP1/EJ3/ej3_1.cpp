#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct dato {
   int valor;
   int posicion_inicial;
};
vector<bool> puede_ser_negativo;
vector<bool> puede_ser_positivo;
vector<int> acumulado_hasta;
vector<vector<bool>> memo;
vector<dato> valores_entrada;
int cantidad_valores;
int saldo;

bool operator<(const dato &d1, const dato &d2) {
    return d1.valor > d2.valor;
}

int suma_total=0;

bool encontrar_negativos(int posicion, int saldo_actual){
    if(posicion == cantidad_valores && saldo_actual == 0){     
      return true;
    }
    else if(saldo_actual < 0){
        return false;
    }
    else if(saldo_actual > 2*acumulado_hasta[posicion]){
        return false;
    }
    else if(posicion < cantidad_valores){
        if (!memo[posicion][saldo_actual]){
            bool valor_anterior = puede_ser_positivo[posicion];
            puede_ser_positivo[posicion] = true;
            bool tiene_signo_positivo = encontrar_negativos(posicion + 1, saldo_actual);
            if(!tiene_signo_positivo){
                puede_ser_positivo[posicion] = valor_anterior; 
            }
            
            bool tiene_signo_negativo = false;
            if(saldo_actual >= valores_entrada[posicion].valor){
                valor_anterior = puede_ser_negativo[posicion];
                puede_ser_negativo[posicion] = true;
                tiene_signo_negativo = encontrar_negativos(posicion + 1, saldo_actual - 2*valores_entrada[posicion].valor);
                if(!tiene_signo_negativo){
                    puede_ser_negativo[posicion] = valor_anterior;
                }
            }
            memo[posicion][saldo_actual] = tiene_signo_positivo || tiene_signo_negativo;
            return memo[posicion][saldo_actual];
        }
        return memo[posicion][saldo_actual];
    }
    return false;
}

int main() {
    int case_tests;
    cin >> case_tests;
    for (int i = 0; i < case_tests; i++)
    {
      cin >> cantidad_valores >> saldo;
      if (cantidad_valores > 0){
        puede_ser_negativo = vector<bool> (cantidad_valores, false);
        puede_ser_positivo = vector<bool> (cantidad_valores, false);
        acumulado_hasta = vector<int> (cantidad_valores, 0);
        
        valores_entrada = vector<dato>();
        valores_entrada.reserve(cantidad_valores);
        
        for (int j = 0; j < cantidad_valores; j++)
        {
            int entrada;
            cin >> entrada;
            suma_total += entrada;
            valores_entrada.push_back({entrada,j});
        }
        sort(valores_entrada.begin(), valores_entrada.end());

        acumulado_hasta[cantidad_valores - 1] = valores_entrada[cantidad_valores - 1].valor;
        for (int j = cantidad_valores - 2; j >=0 ; j--)
        {   
            acumulado_hasta[j] = acumulado_hasta[j+1] + valores_entrada[j].valor;
        }
        int acumulacion_total = acumulado_hasta[0];

        //int cantidad_a_restar = (suma_total - saldo)/2;

        acumulacion_total = acumulacion_total - saldo;

        for (int j = 0; j < cantidad_valores; j++)
        {
            vector<bool> test (acumulacion_total + 1 , false);
            memo.push_back(test);
        }

        bool res = encontrar_negativos(0,acumulacion_total);
        suma_total = 0; 
        memo = vector<vector<bool> >();
        acumulado_hasta = vector<int>();
        char resultado[cantidad_valores];
        for (int j = 0; j < cantidad_valores; j++)
        {
            if (puede_ser_negativo[j] && puede_ser_positivo[j]){
                resultado[valores_entrada[j].posicion_inicial]= '?';
            }
            else if(puede_ser_negativo[j]){
                resultado[valores_entrada[j].posicion_inicial]= '-';
            }
            else{
                resultado[valores_entrada[j].posicion_inicial]= '+';
            }
        }
        for (int j = 0; j < cantidad_valores; j++)
        {
            cout << resultado[j];
        }
        
      }
      cout << endl;
   }
   
   return 0;

}

