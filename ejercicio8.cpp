#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Frecuencia {
    char letra;
    int cantidad;
};

void inicializarFrecuencias(Frecuencia frecuencias[]) {
    for (int i = 0; i < 26; i++) {
        frecuencias[i].letra = 'a' + i;
        frecuencias[i].cantidad = 0;
    }
}

int indiceMayorFrecuencia(Frecuencia frecuencias[]) {
    int posMax = 0;

    for (int i = 1; i < 26; i++) {
        if (frecuencias[i].cantidad > frecuencias[posMax].cantidad) {
            posMax = i;
        }
    }

    return posMax;
}

bool esPosible(Frecuencia frecuencias[], int restantes) {
    int posMax = indiceMayorFrecuencia(frecuencias);
    return frecuencias[posMax].cantidad <= (restantes + 1) / 2;
}

int main() {
    string s;
    cin >> s;

    int n = s.length();
    Frecuencia frecuencias[26];

    inicializarFrecuencias(frecuencias);

    for (int i = 0; i < n; i++) {
        int pos = s[i] - 'a';
        frecuencias[pos].cantidad++;
    }

    if (!esPosible(frecuencias, n)) {
        cout << "Imposible" << endl;
        return 0;
    }

    char* resultado = new char[n];
    char anterior = ' ';
    bool hayAnterior = false;

    for (int i = 0; i < n; i++) {
        bool encontre = false;
        int restantesDespues = n - i - 1;

        for (int letra = 25; letra >= 0 && !encontre; letra--) {
            if (frecuencias[letra].cantidad > 0 && (!hayAnterior || frecuencias[letra].letra != anterior)) {
                frecuencias[letra].cantidad--;

                if (esPosible(frecuencias, restantesDespues)) {
                    resultado[i] = frecuencias[letra].letra;
                    anterior = resultado[i];
                    hayAnterior = true;
                    encontre = true;
                } else {
                    frecuencias[letra].cantidad++;
                }
            }
        }

        if (!encontre) {
            delete[] resultado;
            cout << "Imposible" << endl;
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << resultado[i];
    }
    cout << endl;

    delete[] resultado;
    return 0;
}
