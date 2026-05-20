#include <string>
#include <iostream>
#include <math.h>
#include <climits>
using namespace std;

struct Asociacion {
    string clave;
    long long valor;

    Asociacion(string unaClave, long long unValor)
        : clave(unaClave), valor(unValor) {}
};

class TablaHashCerrada_Agenda
{
private:
	Asociacion **array;
	int tamanio;
	int cantidadDeElementos;

	bool esPrimo(int n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;

        for (long long i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }

        return true;
    }

	int siguientePrimo(int n) {
        while (!esPrimo(n)) {
            n++;
        }
        return n;
    }

	float factorDeCarga()
	{
		return (float)this->cantidadDeElementos / this->tamanio;
	}

	int fnHash(string clave, int modulo) {
        unsigned long long hash = 0;

        for (int i = 0; i < (int)clave.length(); i++) {
            hash = (hash * 131 + (unsigned char)clave[i]) % modulo;
        }

        return (int)hash;
    }

    int fnHash2(string clave, int modulo) {
        unsigned long long hash = 5381 % modulo;

        for (int i = 0; i < (int)clave.length(); i++) {
            hash = (hash * 33 + (unsigned char)clave[i]) % modulo;
        }

        return (int)hash;
    }

	int posicionTentativa(int i, string clave)
	{
    	int h1 = normalizar(fnHash(clave));
    	int h2 = 1 + (fnHash2(clave) % (tamanio - 1));

   	 	return (h1 + i * h2) % tamanio;
	}

    int buscarPosicion(string clave) {
        for (int i = 0; i < tamanio; i++) {
            int pos = posicionTentativa(i, clave);

            if (array[pos] == NULL) {
                return pos;
            }

            if (array[pos]->clave == clave) {
                return pos;
            }
        }

        return -1;
    }
	void rehash() {
        Asociacion** arrayAnterior = array;
        int tamanioAnterior = tamanio;

        int nuevoTamanio = siguientePrimo(tamanio * 2);

        array = new Asociacion*[nuevoTamanio]();
        tamanio = nuevoTamanio;
        cantidadDeElementos = 0;

        for (int i = 0; i < tamanioAnterior; i++) {
            if (arrayAnterior[i] != NULL) {
                insertar(arrayAnterior[i]->clave, arrayAnterior[i]->valor);
                delete arrayAnterior[i];
            }
        }

        delete[] arrayAnterior;
    }

public:
	TablaHashCerrada_Agenda(int tamaniInicial)
	{
		this->tamanio = this->siguientePrimo(tamaniInicial);
		this->cantidadDeElementos = 0;
		array = new Asociacion *[this->tamanio]();
	}

	~TablaHashCerrada_Agenda() {
        for (int i = 0; i < tamanio; i++) {
            if (array[i] != NULL) {
                delete array[i];
            }
        }

        delete[] array;
    }
	 void insertar(string clave, long long valor) {
        int pos = buscarPosicion(clave);

        if (array[pos] == NULL) {
            array[pos] = new Asociacion(clave, valor);
            cantidadDeElementos++;
        } else {
            array[pos]->valor = valor;
        }

        if (factorDeCarga() > 0.7) {
            rehash();
        }
    }

	void sumar(string clave, long long valorASumar) {
        int pos = buscarPosicion(clave);

        if (array[pos] == NULL) {
            array[pos] = new Asociacion(clave, valorASumar);
            cantidadDeElementos++;
        } else {
            array[pos]->valor += valorASumar;
        }

        if (factorDeCarga() > 0.7) {
            rehash();
        }
    }

    int obtener(string clave) {
        int pos = buscarPosicion(clave);

        if (pos == -1 || array[pos] == NULL) {
            return 0;
        }

        return array[pos]->valor;
    }

    int obtenerMaximo() {
        int maximo = INT_MIN;

        for (int i = 0; i < tamanio; i++) {
            if (array[i] != NULL) {
                if (array[i]->valor > maximo) {
                    maximo = array[i]->valor;
                }
            }
        }

        return maximo;
    }
};

