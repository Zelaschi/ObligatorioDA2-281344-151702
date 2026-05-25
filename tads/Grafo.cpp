#include "Grafo.h"

#include <climits>

#include "minHeap.cpp"

Grafo::Grafo(int cantidadVertices) {
    this->cantidadVertices = cantidadVertices;
    this->adyacentes = new Nodo*[cantidadVertices + 1];

    for (int i = 1; i <= cantidadVertices; i++) {
        adyacentes[i] = 0;
    }
}

Grafo::~Grafo() {
    for (int i = 1; i <= cantidadVertices; i++) {
        Nodo* actual = adyacentes[i];

        while (actual != 0) {
            Nodo* aBorrar = actual;
            actual = actual->siguiente;
            delete aBorrar;
        }
    }

    delete[] adyacentes;
}

void Grafo::agregarAdyacente(int origen, int destino, int peso) {
    Nodo* nuevo = new Nodo;
    nuevo->destino = destino;
    nuevo->peso = peso;
    nuevo->siguiente = adyacentes[origen];
    adyacentes[origen] = nuevo;
}

int Grafo::getCantidadVertices() {
    return cantidadVertices;
}

Grafo::Nodo* Grafo::obtenerAdyacentes(int vertice) {
    return adyacentes[vertice];
}

void Grafo::agregarArista(int origen, int destino, int peso) {
    agregarAdyacente(origen, destino, peso);
    agregarAdyacente(destino, origen, peso);
}

long long Grafo::costoMinimo(int origen, int destino) {
    int vertices = cantidadVertices;
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

            Nodo* adyacentes = this->adyacentes[verticeActual];

            while (adyacentes != 0) {
                int verticeAdy = adyacentes->destino;
                int peso = adyacentes->peso;

                if (!visitados[verticeAdy] && costos[verticeActual] != INF &&
                    costos[verticeAdy] > costos[verticeActual] + peso) {
                    costos[verticeAdy] = costos[verticeActual] + peso;
                    heap->insertar(verticeAdy, costos[verticeAdy]);
                }

                adyacentes = adyacentes->siguiente;
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

bool Grafo::esBipartito() {
    int* color = new int[cantidadVertices + 1];
    int* cola = new int[cantidadVertices];

    for (int i = 1; i <= cantidadVertices; i++) {
        color[i] = 0;
    }

    for (int inicio = 1; inicio <= cantidadVertices; inicio++) {
        if (color[inicio] == 0) {
            int primero = 0;
            int ultimo = 0;

            color[inicio] = 1;
            cola[ultimo] = inicio;
            ultimo++;

            while (primero < ultimo) {
                int actual = cola[primero];
                primero++;

                Nodo* adyacente = adyacentes[actual];

                while (adyacente != 0) {
                    int vecino = adyacente->destino;

                    if (color[vecino] == 0) {
                        color[vecino] = 3 - color[actual];
                        cola[ultimo] = vecino;
                        ultimo++;
                    } else if (color[vecino] == color[actual]) {
                        delete[] color;
                        delete[] cola;
                        return false;
                    }

                    adyacente = adyacente->siguiente;
                }
            }
        }
    }

    delete[] color;
    delete[] cola;
    return true;
}
