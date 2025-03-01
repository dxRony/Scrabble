#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <stdexcept>
#include "Nodo.h"

using namespace std;

template<typename T>
class Pila {
private:
    Nodo<T> *cima; // apuntador a la cima de la pila

public:
    Pila() {
        //inciando pila con una cima nula
        this->cima = nullptr;
    }

    Nodo<T> *getCima() {
        return this->cima;
    }

    void setCima(Nodo<T> *cima) {
        this->cima = cima;
    }

    void push(T data) {
        //creando nodo dado el dato recibio, actualizando cima con el dato recibido
        auto *nuevoNodo = new Nodo<T>(data);
        nuevoNodo->setNext(this->cima);
        this->cima = nuevoNodo;
    }

    T *pop() {
        if (this->cima == nullptr) return nullptr;
        //nodo que contiene la cima
        Nodo<T> *aux = this->cima;
        //obteniendo el dato de la cima
        T *data = this->cima->getData();
        //actualizando la cima al siguiente nodo y devolviendo la antigua cima
        this->cima = this->cima->getNext();
        delete aux;
        return data;
    }

    bool isEmpty() {
        return this->cima == nullptr;
    }

    void mostrarPila() {
        if (isEmpty()) {
            cout << "La pila está vacía." << endl;
            return;
        }
        //guardando dato desde la cima
        Nodo<T> *actual = this->cima;
        while (actual != nullptr) {
            //mientras exista un dato, se imprime y se avanza al siguiente
            cout << *actual->getData() << ", ";
            actual = actual->getNext();
        }
    }
};
#endif //PILA_H
