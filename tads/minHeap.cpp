#ifndef MINHEAPDIJKSTRA
#define MINHEAPDIJKSTRA

#include <iostream>
using namespace std;

struct NodoHeap{
    int vertice;
    long long costo;

    NodoHeap(){
        vertice = -1;
        costo = 0;
    }

    NodoHeap(int v, long long c){
        vertice = v;
        costo = c;
    }
};

class minHeap{
private:
    NodoHeap* vec;
    int capacidad;
    int primeroLibre;

    bool estaLleno(){
        return this->primeroLibre > this->capacidad;
    }

    int padre(int pos){
        return pos / 2;
    }

    int funcionComparadora(NodoHeap a, NodoHeap b){
        if (a.costo < b.costo) return -1;
        if (a.costo > b.costo) return 1;
        return 0;
    }

    void intercambiar(int posPadre, int pos){
        NodoHeap aux = vec[posPadre];
        vec[posPadre] = vec[pos];
        vec[pos] = aux;
    }

    void flotar(int pos){
        if(pos > 1){
            int posPadre = padre(pos);

            if(funcionComparadora(vec[posPadre], vec[pos]) > 0){
                intercambiar(posPadre, pos);
                flotar(posPadre);
            }
        }
    }

    int izq(int pos){
        return pos * 2;
    }

    int der(int pos){
        return pos * 2 + 1;
    }

    void hundir(int pos){
        int posHijoIzq = izq(pos);
        int posHijoDer = der(pos);

        if(posHijoIzq < this->primeroLibre && posHijoDer < this->primeroLibre){
            int posHijoMenor = funcionComparadora(vec[posHijoIzq], vec[posHijoDer]) > 0 ? posHijoDer : posHijoIzq;

            if(funcionComparadora(vec[pos], vec[posHijoMenor]) > 0){
                intercambiar(pos, posHijoMenor);
                hundir(posHijoMenor);
            }
        }
        else{
            if(posHijoIzq < this->primeroLibre){
                if(funcionComparadora(vec[pos], vec[posHijoIzq]) > 0){
                    intercambiar(pos, posHijoIzq);
                    hundir(posHijoIzq);
                }
            }
        }
    }

    void agrandar(){
        int nuevaCapacidad = this->capacidad * 2;
        NodoHeap* nuevoVec = new NodoHeap[nuevaCapacidad + 1];

        for(int i = 1; i < this->primeroLibre; i++){
            nuevoVec[i] = this->vec[i];
        }

        delete[] this->vec;
        this->vec = nuevoVec;
        this->capacidad = nuevaCapacidad;
    }

public:
    minHeap(int capacidad){
        this->vec = new NodoHeap[capacidad + 1];
        this->capacidad = capacidad;
        this->primeroLibre = 1;
    }

    ~minHeap(){
        delete[] this->vec;
    }

    void insertar(int vertice, long long costo){
        if(this->estaLleno()){
            agrandar();
        }

        this->vec[this->primeroLibre] = NodoHeap(vertice, costo);
        flotar(this->primeroLibre);
        this->primeroLibre++;
    }

    void eliminar(){
        if(estaVacio()){
            return;
        }

        this->vec[1] = this->vec[primeroLibre - 1];
        this->primeroLibre--;
        hundir(1);
    }

    NodoHeap tope(){
        if(this->primeroLibre == 1){
            return NodoHeap();
        }

        return this->vec[1];
    }

    bool estaVacio(){
        return this->primeroLibre == 1;
    }
};

#endif
