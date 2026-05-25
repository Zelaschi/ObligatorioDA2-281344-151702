#include "ColaPriodidadPaciente.h"

ColaPrioridad::ColaPrioridad(int capacidad) {
    this->heap = new Paciente[capacidad];
    this->cantidad = 0;
}

ColaPrioridad::~ColaPrioridad() {
    delete[] heap;
}

bool ColaPrioridad::mayorPrioridad(Paciente a, Paciente b) {
    if (a.urgencia != b.urgencia) {
        return a.urgencia > b.urgencia;
    }

    if (a.hora != b.hora) {
        return a.hora < b.hora;
    }

    return a.orden < b.orden;
}

void ColaPrioridad::intercambiar(int i, int j) {
    Paciente aux = heap[i];
    heap[i] = heap[j];
    heap[j] = aux;
}

void ColaPrioridad::flotar(int pos) {
    while (pos > 0) {
        int padre = (pos - 1) / 2;

        if (!mayorPrioridad(heap[pos], heap[padre])) {
            break;
        }

        intercambiar(pos, padre);
        pos = padre;
    }
}

void ColaPrioridad::hundir(int pos) {
    while (true) {
        int hijoIzq = 2 * pos + 1;
        int hijoDer = 2 * pos + 2;
        int mayor = pos;

        if (hijoIzq < cantidad && mayorPrioridad(heap[hijoIzq], heap[mayor])) {
            mayor = hijoIzq;
        }

        if (hijoDer < cantidad && mayorPrioridad(heap[hijoDer], heap[mayor])) {
            mayor = hijoDer;
        }

        if (mayor == pos) {
            break;
        }

        intercambiar(pos, mayor);
        pos = mayor;
    }
}

void ColaPrioridad::encolar(Paciente paciente) {
    heap[cantidad] = paciente;
    flotar(cantidad);
    cantidad++;
}

Paciente ColaPrioridad::desencolar() {
    Paciente maximo = heap[0];
    cantidad--;

    if (cantidad > 0) {
        heap[0] = heap[cantidad];
        hundir(0);
    }

    return maximo;
}

bool ColaPrioridad::esVacia() {
    return cantidad == 0;
}