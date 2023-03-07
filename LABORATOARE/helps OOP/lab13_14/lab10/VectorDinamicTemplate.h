//
// Created by Laura on 4/8/2022.
//
#pragma once
#ifndef UNTITLED_VECTORDINAMICTEMPLATE_H
#define UNTITLED_VECTORDINAMICTEMPLATE_H



constexpr auto INITIAL_CAPACITY = 10;
#include <assert.h>
#include <vector>

template<typename T>
class IteratorVector;



template<typename T>
class VectorDinamic {
private:
    //reprezentare
    T* elems;
    int capacitate;
    int lungime;

    void resize();
public:


    //default constructor
    VectorDinamic();

    //copy constructor
    VectorDinamic(const VectorDinamic& ot);

    //assignment operator
    VectorDinamic& operator=(const VectorDinamic& ot);

    VectorDinamic& operator=(VectorDinamic&& ot) noexcept ;

    //destructor
    ~VectorDinamic();

    //add element in vector
    void add(T elem);

    //get element from position in vector
    T& get(int poz) noexcept;

    //set element on position in vector
    void set(T elem, int poz) noexcept;

    //get size - length of vector
    int size() noexcept;

    void remove(int index);

    friend class IteratorVector<T>;

    IteratorVector<T> begin() noexcept;
    IteratorVector<T> end() noexcept;

};

template<typename T>
class IteratorVector {
private:
    const VectorDinamic<T>& vec;
    int poz = 0;
public:
    IteratorVector(const VectorDinamic<T>& v) noexcept;
    IteratorVector(const VectorDinamic<T>& v, int poz) noexcept;
    bool valid() const;
    T& element() const;
    void next() noexcept;
    T& operator*();
    IteratorVector& operator++() noexcept;
    bool operator==(const IteratorVector& ot) noexcept;
    bool operator!=(const IteratorVector& ot) noexcept;
};

template<typename T>
VectorDinamic<T>::VectorDinamic() {
    this->elems = new T[INITIAL_CAPACITY];
    this->lungime = 0;
    this->capacitate = INITIAL_CAPACITY;
}

template<typename T>
VectorDinamic<T>::VectorDinamic(const VectorDinamic& ot) {
    //constructor de copiere (creeare vector dinamic nou pe baza celui existent

    this->elems = new T[ot.capacitate];
    for (int i = 0; i < ot.lungime; i++) {
        this->elems[i] = ot.elems[i];
    }
    this->lungime = ot.lungime;
    this->capacitate = ot.capacitate;
}
//DE LA ISTVAN
template<typename T>
VectorDinamic<T>& VectorDinamic<T>::operator=(VectorDinamic&& ot)  noexcept {
    if (this == &ot) {
        return *this;
    }
    delete[] elems;
    // Copy the data pointer from other
    elems = ot.elems;
    lungime = ot.lungime;
    capacitate = ot.capacitate;

    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times.
    ot.elems = nullptr;
    ot.lungime = 0;
    ot.capacitate = 0;
    return *this;
}

template<typename T>
VectorDinamic<T>& VectorDinamic<T>::operator=(const VectorDinamic& ot) {

    if (this == &ot) {
        return *this;
    }
    //fiindca in obiectul curent punem altceva prin assignment, eliberam memoria alocata anterior

    delete[] this->elems;

    //copiem elementele din ot si setam lungime, capacitate
    this->elems = new T[ot.capacitate];
    for (int i = 0; i < ot.lungime; i++) {
        elems[i] = ot.elems[i];  //utilizeaza operator assignment aferent tipului T
    }
    this->lungime = ot.lungime;
    this->capacitate = ot.capacitate;
    return *this;
}
template<typename T>
void VectorDinamic<T>::resize() {
    const int newCapacity = this->capacitate * 2;
    T* newElems = new T[newCapacity];
    for (int i = 0; i < this->lungime; i++) {
        newElems[i] = this->elems[i];
    }
    delete[] this->elems;
    this->elems = newElems;
    this->capacitate = newCapacity;

}
template<typename T>
VectorDinamic<T>::~VectorDinamic() {
    delete[] this->elems;
}
template<typename T>
void VectorDinamic<T>::add(T elem) {
    if (this->lungime == this->capacitate)
        resize();
    int i=this->lungime;
    this->elems[(i)] = elem;
    this->lungime++;
}

template<typename T>
void VectorDinamic<T>::remove(int index) {
    if (index < 0 || index >= this->lungime)
        return;
    for (int i = index; i < this->lungime - 1; i++)
        this->elems[i] = this->elems[i + 1];
    this->lungime--;
}

template<typename T>
T& VectorDinamic<T>::get(int poz) noexcept {
    return this->elems[poz];
}



template<typename T>
void VectorDinamic<T>::set(T elem, int poz) noexcept {
    this->elems[poz] = elem;
}

template<typename T>
int VectorDinamic<T>::size() noexcept  {
    return this->lungime;
}

template<typename T>
IteratorVector<T> VectorDinamic<T>::begin() noexcept {
    return IteratorVector<T>(*this);
}
template<typename T>
IteratorVector<T> VectorDinamic<T>::end() noexcept {
    return IteratorVector<T>(*this, this->lungime);
}



template<typename T>
IteratorVector<T>::IteratorVector(const VectorDinamic<T>& v) noexcept :vec{ v } { };
template<typename T>
IteratorVector<T>::IteratorVector(const VectorDinamic<T>& v, int poz) noexcept :vec{ v }, poz{ poz }{};

template<typename T>
bool IteratorVector<T>::valid() const {
    return this->poz < this->vec.lungime;
}
template<typename T>
T& IteratorVector<T>::element() const {
    return this->vec.elems[this->poz];
}
template<typename T>
void IteratorVector<T>::next() noexcept{
    this->poz++;
}

template<typename T>
T& IteratorVector<T>::operator*() {
    return this->element();
}

template<typename T>
IteratorVector<T>& IteratorVector<T>::operator++() noexcept{
    this->next();
    return *this;
}

template<typename T>
bool IteratorVector<T>::operator==(const IteratorVector& ot) noexcept {
    return this->poz == ot.poz;
}
template<typename T>
bool IteratorVector<T>::operator!=(const IteratorVector& ot) noexcept {
    return !(*this == ot);
}











#endif //UNTITLED_VECTORDINAMICTEMPLATE_H
