#ifndef COLA_PRIORIDAD_H
#define COLA_PRIORIDAD_H

#include <string>

using namespace std;

struct Paciente {
    int id;
    string hora;
    int urgencia;
    int orden;
};

class ColaPrioridad {
private:
    Paciente* heap;
    int cantidad;

    bool mayorPrioridad(Paciente a, Paciente b);
    void intercambiar(int i, int j);
    void flotar(int pos);
    void hundir(int pos);

public:
    ColaPrioridad(int capacidad);
    ~ColaPrioridad();

    void encolar(Paciente paciente);
    Paciente desencolar();
    bool esVacia();
};

#endif