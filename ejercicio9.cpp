#include <string>
#include <iostream>

using namespace std;

struct Objeto {
    int peso;
    int volumen;
    int costo;
    int valor;
    int supervivencia;
    int comida;
};

struct Solucion {
    int valor;
    int peso;
    int cantidad;
};

int posicion(int pesoActual, int volumenActual, int costoActual, int supervivenciaActual, int comidaActual, int volumenMaximo, int costoMaximo, int supervivenciaMaxima, int comidaMaxima) {
    return (((((pesoActual * (volumenMaximo + 1) + volumenActual) * (costoMaximo + 1) + costoActual) * (supervivenciaMaxima + 1) + supervivenciaActual) * (comidaMaxima + 1)) + comidaActual);
}

bool esMejor(Solucion nueva, Solucion actual) {
    if (nueva.valor != actual.valor) {
        return nueva.valor > actual.valor;
    }

    if (nueva.peso != actual.peso) {
        return nueva.peso < actual.peso;
    }

    return nueva.cantidad < actual.cantidad;
}

Solucion agregarObjeto(Solucion solucionAnterior, Objeto objetoActual) {
    Solucion nueva;
    nueva.valor = solucionAnterior.valor + objetoActual.valor;
    nueva.peso = solucionAnterior.peso + objetoActual.peso;
    nueva.cantidad = solucionAnterior.cantidad + 1;
    return nueva;
}

int main() {
    int n;
    cin >> n;

    int pesoMaximo, volumenMaximo, costoMaximo, supervivenciaMaxima, comidaMaxima;
    cin >> pesoMaximo >> volumenMaximo >> costoMaximo >> supervivenciaMaxima >> comidaMaxima;

    Objeto* objetos = new Objeto[n];

    for (int i = 0; i < n; i++) {
        string categoria;
        cin >> objetos[i].peso >> objetos[i].volumen >> objetos[i].costo >> objetos[i].valor >> categoria;

        if (categoria == "supervivencia") {
            objetos[i].supervivencia = 1;
            objetos[i].comida = 0;
        } else {
            objetos[i].supervivencia = 0;
            objetos[i].comida = 1;
        }
    }

    int cantidadEstados = (pesoMaximo + 1) * (volumenMaximo + 1) * (costoMaximo + 1) * (supervivenciaMaxima + 1) * (comidaMaxima + 1);
    Solucion* dp = new Solucion[cantidadEstados]();

    for (int objetoActual = 0; objetoActual < n; objetoActual++) {
        Objeto objeto = objetos[objetoActual];

        for (int pesoActual = pesoMaximo; pesoActual >= objeto.peso; pesoActual--) {
            for (int volumenActual = volumenMaximo; volumenActual >= objeto.volumen; volumenActual--) {
                for (int costoActual = costoMaximo; costoActual >= objeto.costo; costoActual--) {
                    for (int supervivenciaActual = supervivenciaMaxima; supervivenciaActual >= objeto.supervivencia; supervivenciaActual--) {
                        for (int comidaActual = comidaMaxima; comidaActual >= objeto.comida; comidaActual--) {
                            int posActual = posicion(pesoActual, volumenActual, costoActual, supervivenciaActual, comidaActual, volumenMaximo, costoMaximo, supervivenciaMaxima, comidaMaxima);
                            int posAnterior = posicion(pesoActual - objeto.peso, volumenActual - objeto.volumen, costoActual - objeto.costo, supervivenciaActual - objeto.supervivencia, comidaActual - objeto.comida, volumenMaximo, costoMaximo, supervivenciaMaxima, comidaMaxima);

                            Solucion valorDeUsarElObjeto = agregarObjeto(dp[posAnterior], objeto);
                            Solucion valorDeNoUsarElObjeto = dp[posActual];

                            if (esMejor(valorDeUsarElObjeto, valorDeNoUsarElObjeto)) {
                                dp[posActual] = valorDeUsarElObjeto;
                            }
                        }
                    }
                }
            }
        }
    }

    int posRespuesta = posicion(pesoMaximo, volumenMaximo, costoMaximo, supervivenciaMaxima, comidaMaxima, volumenMaximo, costoMaximo, supervivenciaMaxima, comidaMaxima);
    Solucion respuesta = dp[posRespuesta];

    cout << respuesta.valor << " " << respuesta.peso << " " << respuesta.cantidad << '\n';

    delete[] objetos;
    delete[] dp;

    return 0;
}
