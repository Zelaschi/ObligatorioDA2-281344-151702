#include <string>
#include <iostream>

using namespace std;

struct Competidor {
    int indice;
    int total;
};

bool esSolucionTrivial(int inicio, int fin) {
    return inicio >= fin;
}

int dividirIzq(int inicio, int fin) {
    return (inicio + fin) / 2;
}

int dividirDer(int inicio, int fin) {
    return ((inicio + fin) / 2) + 1;
}

void merge(Competidor competidores[], Competidor aux[], int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    int k = inicio;

    while (i <= medio && j <= fin) {
        if (competidores[i].total <= competidores[j].total) {
            aux[k] = competidores[i];
            i++;
        } else {
            aux[k] = competidores[j];
            j++;
        }
        k++;
    }

    while (i <= medio) {
        aux[k] = competidores[i];
        i++;
        k++;
    }

    while (j <= fin) {
        aux[k] = competidores[j];
        j++;
        k++;
    }

    for (int pos = inicio; pos <= fin; pos++) {
        competidores[pos] = aux[pos];
    }
}

void mergeSort(Competidor competidores[], Competidor aux[], int inicio, int fin) {
    if (esSolucionTrivial(inicio, fin)) {
        return;
    }

    int finIzq = dividirIzq(inicio, fin);
    int inicioDer = dividirDer(inicio, fin);

    mergeSort(competidores, aux, inicio, finIzq);
    mergeSort(competidores, aux, inicioDer, fin);

    merge(competidores, aux, inicio, finIzq, fin);
}

int main() {
    int l;
    cin >> l;

    Competidor* competidores = new Competidor[l];
    Competidor* aux = new Competidor[l];

    for (int i = 0; i < l; i++) {
        int tiempoNatacion;
        cin >> tiempoNatacion;

        competidores[i].indice = i + 1;
        competidores[i].total = tiempoNatacion;
    }

    for (int i = 0; i < l; i++) {
        int tiempoCiclismo;
        cin >> tiempoCiclismo;

        competidores[i].total += tiempoCiclismo;
    }

    for (int i = 0; i < l; i++) {
        int tiempoCarrera;
        cin >> tiempoCarrera;

        competidores[i].total += tiempoCarrera;
    }

    mergeSort(competidores, aux, 0, l - 1);

    for (int i = 0; i < l; i++) {
        cout << competidores[i].indice << '\n';
    }

    delete[] competidores;
    delete[] aux;

    return 0;
}
