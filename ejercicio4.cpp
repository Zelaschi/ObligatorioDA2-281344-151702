#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/HashStringCerrado.h"
#include "tads/DijkstraPlanetario.h"

using namespace std;

int obtenerIndicePlaneta(TablaHashCerrada& indices, string nombre, int& proximoIndice) {
    int indice = indices.obtener(nombre);

    if (indice == 0) {
        indice = proximoIndice;
        indices.insertar(nombre, indice);
        proximoIndice++;
    }

    return indice;
}

int main() {
    int n, m;
    cin >> n >> m;

    TablaHashCerrada indices(n * 2 + 1);
    GrafoDijkstra grafo(n);
    int proximoIndice = 1;

    for (int i = 0; i < m; i++) {
        string planetaA, planetaB;
        int costo;

        cin >> planetaA >> planetaB >> costo;

        int indiceA = obtenerIndicePlaneta(indices, planetaA, proximoIndice);
        int indiceB = obtenerIndicePlaneta(indices, planetaB, proximoIndice);

        grafo.insertarAristaBidireccional(indiceA, indiceB, costo);
    }

    string origen, destino;
    cin >> origen >> destino;

    if (origen == destino) {
        cout << 0 << '\n';
        return 0;
    }

    int indiceOrigen = indices.obtener(origen);
    int indiceDestino = indices.obtener(destino);

    if (indiceOrigen == 0 || indiceDestino == 0) {
        cout << -1 << '\n';
        return 0;
    }

    cout << grafo.costoMinimo(indiceOrigen, indiceDestino) << '\n';

    return 0;
}
