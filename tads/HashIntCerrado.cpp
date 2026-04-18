#include "HashIntCerrado.h"

HashInt::HashInt(int maxSize, int (*fHash)(int)) {
    this->maxSize = maxSize;
    this->fHash = fHash;
    this->size = 0;
    this->hash = new int[maxSize];
    for (int i = 0; i < maxSize; i++) {
        hash[i] = 0;
    }
}

HashInt::~HashInt() {
    delete[] hash;
}

int HashInt::indexOf(int element) const {
    int idx = fHash(element) % maxSize;
    if (idx < 0) idx += maxSize;
    return idx;
}

void HashInt::insert(int element) {
    int idx = indexOf(element);
    hash[idx]++;
    size++;
}

void HashInt::remove(int element) {
    int idx = indexOf(element);
    size -= hash[idx];
    hash[idx] = 0;
}

bool HashInt::isEmpty() {
    return size == 0;
}

int HashInt::count(int element) const {
    int idx = indexOf(element);
    return hash[idx];
}

bool HashInt::contains(int element) {
    return count(element) > 0;
}

void HashInt::addOne(int element) {
    insert(element);
}

void HashInt::removeOne(int element) {
    int idx = indexOf(element);
    if (hash[idx] > 0) {
        hash[idx]--;
        size--;
    }
}