#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
long long modulo = 1e9 + 7;

struct parcial {
    long long tiempo;
    long long costo;
};

bool operator<(const parcial &p1, const parcial &p2) {
    double r1 = (double)p1.costo / (double)p1.tiempo;
    double r2 = (double)p2.costo / (double)p2.tiempo;
    return r1 > r2;
}

int main() {
    long long test_cases;
    cin >> test_cases;
    long long entries;
    vector<long long> tiempo;
    vector<long long> costo;
    vector<parcial> parciales;
    for(long long i = 0;i<test_cases;++i){
        entries = 0;
        cin >> entries;
        tiempo = vector<long long>();
        costo = vector<long long>();
        for (long long i = 0; i < entries; ++i) {
            long long ent;
            cin >> ent;
            tiempo.push_back(ent);
        }
        for (long long i = 0; i < entries; ++i) {
            long long ent;
            cin >> ent;
            costo.push_back(ent);
        }
        parciales = vector<parcial>();
        parciales.reserve(tiempo.size());
        for (long long i = 0; i < tiempo.size(); ++i) {
            parciales.push_back({tiempo[i], costo[i]});
        }

        sort(begin(parciales), end(parciales));

        long long t = 0;
        long long d = 0;
        for (long long i = 0; i < parciales.size(); ++i) {
            t += parciales[i].tiempo;
            d = (d % modulo + (parciales[i].costo * t) % modulo );
        }

        cout << d % modulo << endl;
    }
    return 0;
}
