#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/HashStringCerrado.cpp"
using namespace std;

struct Ronda {
    string nombre;
    int puntaje;
};

int main() {
    
    int n;
    cin >> n;

    Ronda* rondas = new Ronda[n];

    TablaHashCerrada_Agenda puntajesFinales(n * 2 + 1);

    for (int i = 0; i < n; i++) {
        cin >> rondas[i].nombre >> rondas[i].puntaje;

        puntajesFinales.sumar(rondas[i].nombre, rondas[i].puntaje);
    }

    int maximoFinal = puntajesFinales.obtenerMaximo();

    TablaHashCerrada_Agenda puntajesParciales(n * 2 + 1);

    for (int i = 0; i < n; i++) {
        string nombre = rondas[i].nombre;
        int puntaje = rondas[i].puntaje;

        puntajesParciales.sumar(nombre, puntaje);

        int puntajeParcial = puntajesParciales.obtener(nombre);
        int puntajeFinal = puntajesFinales.obtener(nombre);

        if (puntajeFinal == maximoFinal && puntajeParcial >= maximoFinal) {
            cout << nombre << '\n';
            break;
        }
    }

    delete[] rondas;

    return 0;
}