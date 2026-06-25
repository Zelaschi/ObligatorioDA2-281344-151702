#include <iostream>

using namespace std;

struct Punto {
    long long x;
    long long y;
};

long long valorAbsoluto(long long n) {
    if (n < 0) {
        return -n;
    }

    return n;
}

long long cuadrado(long long n) {
    return n * n;
}

bool esSolucionTrivial(int inicio, int fin) {
    return inicio >= fin;
}

int dividirIzq(int inicio, int fin) {
    return (inicio + fin) / 2;
}

int dividirDer(int inicio, int fin) {
    return ((inicio + fin) / 2) + 1;
}

bool vaAntesPorX(Punto a, Punto b) {
    if (a.x == b.x) {
        return a.y <= b.y;
    }

    return a.x < b.x;
}

bool vaAntesPorY(Punto a, Punto b) {
    if (a.y == b.y) {
        return a.x <= b.x;
    }

    return a.y < b.y;
}

void mergePorX(Punto puntos[], Punto aux[], int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    int k = inicio;

    while (i <= medio && j <= fin) {
        if (vaAntesPorX(puntos[i], puntos[j])) {
            aux[k] = puntos[i];
            i++;
        } else {
            aux[k] = puntos[j];
            j++;
        }
        k++;
    }

    while (i <= medio) {
        aux[k] = puntos[i];
        i++;
        k++;
    }

    while (j <= fin) {
        aux[k] = puntos[j];
        j++;
        k++;
    }

    for (int pos = inicio; pos <= fin; pos++) {
        puntos[pos] = aux[pos];
    }
}

void mergeSortPorX(Punto puntos[], Punto aux[], int inicio, int fin) {
    if (esSolucionTrivial(inicio, fin)) {
        return;
    }

    int finIzq = dividirIzq(inicio, fin);
    int inicioDer = dividirDer(inicio, fin);

    mergeSortPorX(puntos, aux, inicio, finIzq);
    mergeSortPorX(puntos, aux, inicioDer, fin);

    mergePorX(puntos, aux, inicio, finIzq, fin);
}

void mergePorY(Punto puntos[], Punto aux[], int inicio, int medio, int fin) {
    int i = inicio;
    int j = medio + 1;
    int k = inicio;

    while (i <= medio && j <= fin) {
        if (vaAntesPorY(puntos[i], puntos[j])) {
            aux[k] = puntos[i];
            i++;
        } else {
            aux[k] = puntos[j];
            j++;
        }
        k++;
    }

    while (i <= medio) {
        aux[k] = puntos[i];
        i++;
        k++;
    }

    while (j <= fin) {
        aux[k] = puntos[j];
        j++;
        k++;
    }

    for (int pos = inicio; pos <= fin; pos++) {
        puntos[pos] = aux[pos];
    }
}

void mergeSortPorY(Punto puntos[], Punto aux[], int inicio, int fin) {
    if (esSolucionTrivial(inicio, fin)) {
        return;
    }

    int finIzq = dividirIzq(inicio, fin);
    int inicioDer = dividirDer(inicio, fin);

    mergeSortPorY(puntos, aux, inicio, finIzq);
    mergeSortPorY(puntos, aux, inicioDer, fin);

    mergePorY(puntos, aux, inicio, finIzq, fin);
}

bool calcularDistancia(Punto a, Punto b, long long d) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;

    return cuadrado(dx) + cuadrado(dy) <= cuadrado(d);
}

bool calcularDistancia(Punto puntos[], int inicio, int fin, long long d) {
    return calcularDistancia(puntos[inicio], puntos[fin], d);
}

bool resolver(Punto puntos[], int inicio, int fin, long long d) {
    int cantidad = fin - inicio + 1;

    if (cantidad < 2) {
        return false;
    }

    if (cantidad == 2) {
        return calcularDistancia(puntos, inicio, fin, d);
    }

    int medio = dividirIzq(inicio, fin);
    long long xMedio = puntos[medio].x;

    if (resolver(puntos, inicio, medio, d)) {
        return true;
    }

    if (resolver(puntos, medio + 1, fin, d)) {
        return true;
    }

    Punto* banda = new Punto[cantidad];
    int tamBanda = 0;

    for (int i = inicio; i <= fin; i++) {
        if (valorAbsoluto(puntos[i].x - xMedio) <= d) {
            banda[tamBanda] = puntos[i];
            tamBanda++;
        }
    }

    Punto* aux = new Punto[tamBanda];
    mergeSortPorY(banda, aux, 0, tamBanda - 1);

    for (int i = 0; i < tamBanda; i++) {
        int j = i + 1;

        while (j < tamBanda && banda[j].y - banda[i].y <= d) {
            if (calcularDistancia(banda[i], banda[j], d)) {
                delete[] banda;
                delete[] aux;
                return true;
            }

            j++;
        }
    }

    delete[] banda;
    delete[] aux;

    return false;
}

bool existeParCritico(Punto puntos[], int n, long long d) {
    if (n < 2) {
        return false;
    }

    Punto* aux = new Punto[n];

    mergeSortPorX(puntos, aux, 0, n - 1);

    delete[] aux;

    return resolver(puntos, 0, n - 1, d);
}

int main() {
    int n;
    long long d;

    cin >> n >> d;

    Punto* puntos = new Punto[n];

    for (int i = 0; i < n; i++) {
        cin >> puntos[i].x >> puntos[i].y;
    }

    if (existeParCritico(puntos, n, d)) {
        cout << "true" << '\n';
    } else {
        cout << "false" << '\n';
    }

    delete[] puntos;

    return 0;
}