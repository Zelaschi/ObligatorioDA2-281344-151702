#include "DijkstraPlanetario.h"

#include <climits>

#include "grafoLA.cpp"
#include "minHeap.cpp"

using namespace std;

GrafoDijkstra::GrafoDijkstra(int vertices) {
    grafo = new GrafoLA(vertices, false, true);
}

GrafoDijkstra::~GrafoDijkstra() {
    delete grafo;
}

void GrafoDijkstra::insertarAristaBidireccional(int origen, int destino, int costo) {
    grafo->insertarArista(origen, destino, costo);
}

long long GrafoDijkstra::costoMinimo(int origen, int destino) {
    int vertices = grafo->getVertices();
    const long long INF = LLONG_MAX;

    long long* costos = new long long[vertices + 1];
    bool* visitados = new bool[vertices + 1]();

    for (int i = 1; i <= vertices; i++) {
        costos[i] = INF;
    }

    minHeap* heap = new minHeap(vertices * 2 + 1);

    costos[origen] = 0;
    heap->insertar(origen, 0);

    while (!heap->estaVacio()) {
        NodoHeap nodo = heap->tope();
        heap->eliminar();

        int verticeActual = nodo.vertice;

        if (!visitados[verticeActual]) {
            visitados[verticeActual] = true;

            if (verticeActual == destino) {
                break;
            }

            ListaAdyLA adyacentes = grafo->obtenerAdyacentes(verticeActual);

            while (adyacentes != NULL) {
                int verticeAdy = adyacentes->destino;
                int peso = adyacentes->peso;

                if (!visitados[verticeAdy] && costos[verticeActual] != INF &&
                    costos[verticeAdy] > costos[verticeActual] + peso) {
                    costos[verticeAdy] = costos[verticeActual] + peso;
                    heap->insertar(verticeAdy, costos[verticeAdy]);
                }

                adyacentes = adyacentes->sig;
            }
        }
    }

    long long resultado = costos[destino];

    delete heap;
    delete[] costos;
    delete[] visitados;

    if (resultado == INF) {
        return -1;
    }

    return resultado;
}
