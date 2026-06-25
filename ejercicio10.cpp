#include <iostream>

using namespace std;

bool esSolucion(int cartas[], int n, int objetivo) {
    return n == 1 && cartas[0] == objetivo;
}

bool movValido(int a, int b, int operacion) {
    if (operacion == 0) {
        return true;
    }

    if (operacion == 1) {
        return a > b;
    }

    if (operacion == 2) {
        return true;
    }

    return b > 0 && a % b == 0;
}

int calcularMovimiento(int a, int b, int operacion) {
    if (operacion == 0) {
        return a + b;
    }

    if (operacion == 1) {
        return a - b;
    }

    if (operacion == 2) {
        return a * b;
    }

    return a / b;
}

int* crearNuevoArreglo(int cartas[], int n, int posA, int posB, int resultado) {
    int* nuevo = new int[n - 1];
    int posNuevo = 0;

    for (int i = 0; i < n; i++) {
        if (i != posA && i != posB) {
            nuevo[posNuevo] = cartas[i];
            posNuevo++;
        }
    }

    nuevo[posNuevo] = resultado;

    return nuevo;
}

bool backtracking(int cartas[], int n, int objetivo) {
    if (esSolucion(cartas, n, objetivo)) {
        return true;
    }

    if (n == 1) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                for (int operacion = 0; operacion < 4; operacion++) {
                    if (movValido(cartas[i], cartas[j], operacion)) {
                        int resultado = calcularMovimiento(cartas[i], cartas[j], operacion);
                        int* nuevo = crearNuevoArreglo(cartas, n, i, j, resultado);

                        if (backtracking(nuevo, n - 1, objetivo)) {
                            delete[] nuevo;
                            return true;
                        }

                        delete[] nuevo;
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    int n;
    cin >> n;

    int* cartas = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> cartas[i];
    }

    int objetivo;
    cin >> objetivo;

    if (backtracking(cartas, n, objetivo)) {
        cout << 1 << '\n';
    } else {
        cout << 0 << '\n';
    }

    delete[] cartas;

    return 0;
}