#include "Grafo.h"

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

void Grafo::agregarAdyacente(int origen, int destino) {
    Nodo* nuevo = new Nodo;
    nuevo->destino = destino;
    nuevo->siguiente = adyacentes[origen];
    adyacentes[origen] = nuevo;
}

void Grafo::agregarArista(int origen, int destino) {
    agregarAdyacente(origen, destino);
    agregarAdyacente(destino, origen);
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
