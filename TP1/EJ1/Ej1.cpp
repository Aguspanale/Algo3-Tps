#include <iostream>
#include <vector>
using namespace std;

vector<vector<char> > tablero;
vector<vector<vector<int> > > distanciaA;
vector<vector<bool>> recorrido;
vector<vector<vector<int> > > distanciaALimpia;
int rows,columns;

int maximoLargo;
int minimoLargo;

vector<vector<int> > direcciones {{1,0},{0,1},{-1,0},{0,-1}};

vector<int> posibles(int fila, int columna, int direccion);

void caminoMasLargoDesde(int fila, int columna, int direccion,const int largoactual){
    recorrido[fila][columna] = true;
    if(fila == rows-1 && columna == columns-1){
        maximoLargo = max(largoactual,maximoLargo);
        minimoLargo = min(largoactual,minimoLargo);
    } else {
        vector<int> direccionesDisponibles = posibles(fila,columna,direccion);
        for(int dir : direccionesDisponibles){
            bool entraEnLoop = (fila == rows - 1 && dir == 3) || (fila == 0 && dir == 3) || (columna == columns - 1 && dir == 2) || (columna == 0 && dir == 2);
            bool filaEnRango = fila + direcciones[dir][0] >= 0 && fila + direcciones[dir][0] < rows;
            bool columnaEnRango = columna + direcciones[dir][1] >= 0 && columna + direcciones[dir][1] < columns;
            bool noPisado = filaEnRango && columnaEnRango && !recorrido[fila + direcciones[dir][0]][columna + direcciones[dir][1]];
            bool esValida = filaEnRango && columnaEnRango && tablero[fila + direcciones[dir][0]][columna + direcciones[dir][1]] != '#';
            if(noPisado && esValida && !entraEnLoop){
                caminoMasLargoDesde(fila + direcciones[dir][0],columna + direcciones[dir][1],(dir+2) % 4,largoactual+1);
            }
        }
    }
    recorrido[fila][columna] = false;
}



vector<int> posibles(int fila, int columna, int direccion){
    char valor = tablero[fila][columna];
    vector<int> res;
    if(valor == '+'){
        for (int i = 1; i <= 3 ; ++i) {
            res.push_back((direccion + i) % 4);
        }
    }
    if(valor == 'I'){
        res.push_back((direccion + 2) % 4);
    }
    if(valor == 'L'){
        res.push_back((direccion + 1) % 4);
        res.push_back((direccion + 3) % 4);
    }
    return res;
}


void llenar_tablero(){
    tablero = vector<vector<char> >();
    vector<vector<int> > menosunoss;
    recorrido = vector<vector<bool> >();
    distanciaA = vector<vector<vector<int> > >();
    distanciaALimpia = vector<vector<vector<int> > >();
    for (int i = 0; i < rows; i++)
    {
        vector<char> var (columns, 'a');
        vector<int> menosunos (columns, -1);
        vector<bool> falsos (columns, false);
        tablero.push_back(var);
        recorrido.push_back(falsos);
        menosunoss.push_back(menosunos);
    }
    for (int i = 0; i < 4; ++i) {
        distanciaA.push_back(menosunoss);
        distanciaALimpia.push_back(menosunoss);
    }
}
int main() {
    int case_tests;
    bool sepuede;
    cin >> case_tests;
    for (int i = 0; i < case_tests; i++)
    {
        cin >> rows >> columns;
        llenar_tablero();
        int cuentaHashtag = 0;
        for (int j = 0; j < rows; j++)
        {
            for (int k = 0; k < columns; k++)
            {
                cin >> tablero[j][k];
                tablero[j][k] != '#' || cuentaHashtag++;
            }
        }
        sepuede = false;
        minimoLargo = 1e9;
        maximoLargo = -1e9;
        recorrido[0][0] = true;


        if(columns > 1){
            caminoMasLargoDesde(0,1,3,1);
        }
        if(rows > 1){
            caminoMasLargoDesde(1,0,2,1);
        }
        if(minimoLargo < 1000){
            sepuede = true;
        }
        if(sepuede){
            cout << "POSIBLE " << minimoLargo << " " << maximoLargo << endl;
        } else {
            cout << "IMPOSIBLE" << endl;
        }
    }
    return 0;
}
