#ifndef LIST_IMP
#define LIST_IMP

#include "List.h"
#include <cassert>
class HashInt
{
private:
    int *hash;
    int size;
    int maxSize;
    int (*fHash)(int);
public:
    HashInt(int maxSize, int (*fHash)(int))
    {
        this->maxSize = maxSize;
        this->fHash = fHash;
        hash = new int[maxSize];
        for (int i = 0; i < maxSize; i++)
        {
            hash[i] = 0;
        }
        size = 0;
    }
    ~HashInt();
    void insert(int element){
        int index = fHash(element) % maxSize;
        if (hash[index] == 0)
        {
            size++;
        }
        hash[index] = element;
    }
    void remove(int element){
        int index = fHash(element) % maxSize;
        if (hash[index] != 0)
        {
            size--;
        }
        hash[index] = 0;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    bool contains(int element)
    {
        int index = fHash(element) % maxSize;
        return hash[index] == element;
    }
    
    void addOne(int element)
    {
        int index = fHash(element) % maxSize;
        if (hash[index] != 0)
        {
            hash[index]++;
        }
    }
    void removeOne(int element)
    {
        int index = fHash(element) % maxSize;
        if (hash[index] != 0)
        {
            hash[index]--;
        }
    }
};