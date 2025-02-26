//
// Created by ronyrojas on 26/02/25.
//

#ifndef COLA_H
#define COLA_H
#include <iostream>
#include "Nodo.h"
using namespace std;

template<class T>
class Cola {
private:
    Nodo<T> *inicio; // apuntador al frente de la cola frente = inicio
    Nodo<T> *fin; // apuntador al final de la cola    final = fin

public:
    Cola() {
        this->inicio = nullptr;
        this->fin = nullptr;
    }

    int obtenerTamano() {
        int tamano = 0;
        Nodo<T> *actual = this->inicio;
        while (actual != nullptr) {
            tamano++;
            actual = actual->getNext();
        }
        return tamano;
    }

    Nodo<T> *obtenerNodoEnPosicion(int posicion) {
        Nodo<T> *actual = this->inicio;
        for (int i = 0; i < posicion; i++) {
            actual = actual->getNext();
        }
        return actual;
    }

    void mezclarCola() {
        int tamano = obtenerTamano();
        if (tamano <= 1) return;

        for (int i = tamano - 1; i > 0; i--) {
            int j = rand() % (i + 1);

            Nodo<T> *nodoI = obtenerNodoEnPosicion(i);
            Nodo<T> *nodoJ = obtenerNodoEnPosicion(j);

            // Intercambiamos los valores, no los punteros
            T temp = nodoI->getValue();
            nodoI->setValue(nodoJ->getValue());
            nodoJ->setValue(temp);
        }
    }

    Nodo<T> *getInicio() {
        return this->inicio;
    }

    void setInicio(Nodo<T> *inicio) {
        this->inicio = inicio;
    }

    Nodo<T> *getFin() {
        return this->fin;
    }

    void setFin(Nodo<T> *fin) {
        this->fin = fin;
    }

    void encolar(T *dato) {
        auto *nuevoNodo = new Nodo<T>(dato);
        if (this->fin == nullptr) {
            this->inicio = this->fin = nuevoNodo;
            return;
        }
        this->fin->setNext(nuevoNodo);
        this->fin = nuevoNodo;
    }

    void encolar2(T dato) {
        auto *nuevoNodo = new Nodo<T>(dato);
        if (this->fin == nullptr) {
            this->inicio = this->fin = nuevoNodo;
            return;
        }
        this->fin->setNext(nuevoNodo);
        this->fin = nuevoNodo;
    }

    T *desencolar() {
        if (this->inicio == nullptr) return T();

        Nodo<T> *aux = this->inicio;
        T *dato = this->inicio->getData();
        this->inicio = this->inicio->getNext();
        if (this->inicio == nullptr) this->fin = nullptr;

        delete aux;
        return dato;
    }

    T desencolar2() {
        if (this->inicio == nullptr) return T();

        Nodo<T> *aux = this->inicio;
        T *dato = this->inicio->getData();
        this->inicio = this->inicio->getNext();
        if (this->inicio == nullptr) this->fin = nullptr;

        delete aux;
        return *dato;
    }

    bool isVacio() {
        return this->inicio == nullptr;
    }

    void mostrarCola() {
        if (isVacio()) {
            cout << "La cola está vacía." << endl;
            return;
        }

        Nodo<T> *actual = this->inicio;
        while (actual != nullptr) {
            T *dato = actual->getData();
            if (dato != nullptr) {
                cout << *dato << endl; // Asume que T tiene sobrecargado el operador <<
            }
            actual = actual->getNext();
        }
    }
};
#endif //COLA_H
