#ifndef HashIntCerrado_H
#define HashIntCerrado_H

class HashInt
{public:
    // pre: -
    // post: the element is inserted in the hash
    virtual void insert(int element) = 0;

    // pre: -
    // post: remove the element that is equal to the given element
    virtual void remove(int element) = 0;

    // pre: -
    // post: returns if the hash is empty
    virtual bool isEmpty() = 0;

    // pre: -
    // post: returns if the hash contains the given element
    virtual bool contains(int element) = 0;
    
    //pre: -
    //post: add one to the element in the hash
    virtual void addOne(int element) = 0;

    //pre: -
    //post: remove one from the element in the hash
    virtual void removeOne(int element) = 0;
};