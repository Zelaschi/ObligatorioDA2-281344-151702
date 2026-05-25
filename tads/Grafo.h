#ifndef GRAFO_H
#define GRAFO_H

class Grafo {
public:
    struct Nodo {
        int destino;
        int peso;
        Nodo* siguiente;
    };

private:
    Nodo** adyacentes;
    int cantidadVertices;

    void agregarAdyacente(int origen, int destino, int peso);

public:
    Grafo(int cantidadVertices);
    ~Grafo();

    int getCantidadVertices();
    Nodo* obtenerAdyacentes(int vertice);
    void agregarArista(int origen, int destino, int peso = 1);
    long long costoMinimo(int origen, int destino);
    bool esBipartito();
};

#endif
