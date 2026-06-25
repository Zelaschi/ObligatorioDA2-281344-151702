#include <iostream>
#include "tads/ColaPriodidadPaciente.h"
#include "tads/ColaPrioridadPaciente.cpp"

using namespace std;

int main() {
    int n;
    cin >> n;

    ColaPrioridad cola(n);

    for (int i = 0; i < n; i++) {
        Paciente paciente;
        cin >> paciente.id >> paciente.hora >> paciente.urgencia;
        paciente.orden = i;

        cola.encolar(paciente);
    }

    while (!cola.esVacia()) {
        cout << cola.desencolar().id << '\n';
    }

    return 0;
}