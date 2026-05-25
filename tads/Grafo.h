#ifndef GRAFO_H
#define GRAFO_H

class Grafo {
private:
    struct Nodo {
        int destino;
        Nodo* siguiente;
    };

    Nodo** adyacentes;
    int cantidadVertices;

    void agregarAdyacente(int origen, int destino);

public:
    Grafo(int cantidadVertices);
    ~Grafo();

    void agregarArista(int origen, int destino);
    bool esBipartito();
};

#endif
