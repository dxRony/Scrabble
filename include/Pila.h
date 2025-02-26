//
// Created by ronyrojas on 26/02/25.
//

#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <stdexcept>
#include "Nodo.h"

using namespace std;

template<typename T>
class Pila {
private:
    Nodo<T> *raiz; // apuntador al primer elemento de la pila raiz = cima

public:
    Pila() {
        this->raiz = nullptr;
    }

    Nodo<T> *getRaiz() {
        return this->raiz;
    }

    void setRaiz(Nodo<T> *raiz) {
        this->raiz = raiz;
    }

    void push(T data) {
        auto *nuevoNodo = new Nodo<T>(data);
        nuevoNodo->setNext(this->raiz);
        this->raiz = nuevoNodo;
    }

    T *pop() {
        if (this->raiz == nullptr) return nullptr;

        Nodo<T> *aux = this->raiz;
        T *data = this->raiz->getData();
        this->raiz = this->raiz->getNext();
        delete aux;
        return data;
    }

    bool isEmpty() {
        return this->raiz == nullptr;
    }
};
#endif //PILA_H
