#ifndef DIJKSTRA_PLANETARIO_H
#define DIJKSTRA_PLANETARIO_H

class GrafoLA;

class GrafoDijkstra {
private:
    GrafoLA* grafo;

public:
    GrafoDijkstra(int vertices);
    ~GrafoDijkstra();

    void insertarAristaBidireccional(int origen, int destino, int costo);
    long long costoMinimo(int origen, int destino);
};

#endif
