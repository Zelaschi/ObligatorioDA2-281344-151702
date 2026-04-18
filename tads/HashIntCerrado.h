#ifndef HASH_INT_CERRADO_H
#define HASH_INT_CERRADO_H

class HashInt {
private:
    int* hash;
    int maxSize;
    int size;
    int (*fHash)(int);

    int indexOf(int element) const;

public:
    HashInt(int maxSize, int (*fHash)(int));
    ~HashInt();

    void insert(int element);   // Inserta una ocurrencia (multiset)
    void remove(int element);   // Elimina todas las ocurrencias
    bool isEmpty();
    bool contains(int element);

    void addOne(int element);   // +1 ocurrencia
    void removeOne(int element);// -1 ocurrencia (si existe)

    int count(int element) const;
};

#endif