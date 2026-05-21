#ifndef HASH_STRING_CERRADO_H
#define HASH_STRING_CERRADO_H

#include <string>
using namespace std;

struct Asociacion {
    string clave;
    long long valor;

    Asociacion(string unaClave, long long unValor);
};

class TablaHashCerrada
{
private:
    Asociacion **array;
    int tamanio;
    int cantidadDeElementos;

    bool esPrimo(int n);
    int siguientePrimo(int n);
    float factorDeCarga();
    int fnHash(string clave, int modulo);
    int fnHash2(string clave, int modulo);
    int posicionTentativa(int i, string clave);
    int buscarPosicion(string clave);
    void rehash();

public:
    TablaHashCerrada(int tamaniInicial);
    ~TablaHashCerrada();

    void insertar(string clave, long long valor);
    void sumar(string clave, long long valorASumar);
    int obtener(string clave);
    int obtenerMaximo();
};

#endif
