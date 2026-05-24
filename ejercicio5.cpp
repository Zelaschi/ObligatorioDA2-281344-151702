#include <iostream>
#include "tads/Grafo.h"

using namespace std;

int main() {
    int v;
    int a;
    cin >> v >> a;

    Grafo grafo(v);

    for (int i = 0; i < a; i++) {
        int origen;
        int destino;
        cin >> origen >> destino;

        grafo.agregarArista(origen, destino);
    }

    if (grafo.esBipartito()) {
        cout << "SI" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    return 0;
}