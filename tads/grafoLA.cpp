#include <climits>
#include <iostream>
using namespace std;

struct NodoListaLA{
    int destino;
    int peso;
    NodoListaLA* sig;

    NodoListaLA(int d, int p, NodoListaLA* s = NULL){
        destino = d;
        peso = p;
        sig = s;
    }
};

typedef NodoListaLA* ListaAdyLA;

class GrafoLA{
private:
    int V;
    bool dirigido;
    bool ponderado;
    NodoListaLA** vec;

public:
    GrafoLA(int v, bool dirigido = false, bool ponderado = false){
        this->V = v;
        this->vec = new NodoListaLA*[v + 1]();
        this->dirigido = dirigido;
        this->ponderado = ponderado;
    }

    ~GrafoLA(){
        for(int i = 1; i <= V; i++){
            NodoListaLA* act = vec[i];
            while(act != NULL){
                NodoListaLA* borrar = act;
                act = act->sig;
                delete borrar;
            }
        }
        delete[] vec;
    }

    int getVertices(){
        return this->V;
    }

    void insertarArista(int o, int d, int peso = 1){
        if(!ponderado) peso = 1;

        NodoListaLA* nuevo = new NodoListaLA(d, peso, this->vec[o]);
        this->vec[o] = nuevo;

        if(!this->dirigido){
            NodoListaLA* inversa = new NodoListaLA(o, peso, this->vec[d]);
            this->vec[d] = inversa;
        }
    }

    NodoListaLA* obtenerAdyacentes(int v){
        return this->vec[v];
    }
};