//
// Created by ronyrojas on 26/02/25.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <iostream>
#include <stdexcept>
#include "Nodo.h"

using namespace std;

template<class T>
class ListaEnlazada {
private:
    Nodo<T> *raiz; //apuntador al primer nodo (cabeza) de la lista raiz = cabeza
    int size;

public:
    ListaEnlazada() {
        this->raiz = nullptr;
        this->size = 0;
    }

    Nodo<T> *getRaiz() {
        return this->raiz;
    }

    void setRaiz(Nodo<T> *raiz) {
        this->raiz = raiz;
    }

    int getSize() {
        return this->size;
    }

    void setSize(int size) {
        this->size = size;
    }

    Nodo<T> *getElement(int index) {
        if (index < 0 || index >= this->size) return nullptr;

        if (index == 0) return this->raiz;

        int contadorAux = 0;
        Nodo<T> *aux = this->raiz;
        while (contadorAux < index) {
            aux = aux->getNext();
            contadorAux++;
        }
        return aux;
    }

    void insertar(T *value) {
        auto *nuevoNodo = new Nodo<T>(value);
        if (this->raiz == nullptr) {
            this->raiz = nuevoNodo;
            this->size++;
            return;
        }
        Nodo<T> *aux = this->raiz;
        while (aux->getNext() != nullptr) aux = aux->getNext();

        aux->setNext(nuevoNodo);
        this->size++;
    }

    void insertar(T value) {
        auto *nuevoNodo = new Nodo<T>(value);
        if (this->raiz == nullptr) {
            this->raiz = nuevoNodo;
            this->size++;
            return;
        }
        Nodo<T> *aux = this->raiz;
        while (aux->getNext() != nullptr) aux = aux->getNext();

        aux->setNext(nuevoNodo);
        this->size++;
    }

    T *eliminar(T *value) {
        Nodo<T> *aux = this->raiz;
        Nodo<T> *previo = nullptr;
        while (aux != nullptr && aux->getData() != value) {
            previo = aux;
            aux = aux->getNext();
        }
        if (aux == nullptr) return nullptr;

        if (previo != nullptr) {
            previo->setNext(aux->getNext());
        } else {
            this->raiz = aux->getNext();
        }
        aux->setNext(nullptr);
        this->size--;
        return aux->getData();
    }

    Nodo<T> *eliminar(int index) {
        Nodo<T> *aux = this->raiz;
        Nodo<T> *previo = nullptr;
        for (int i = 0; i < index; i++) {
            previo = aux;
            aux = aux->getNext();
        }
        if (previo != nullptr) {
            previo->setNext(aux->getNext());
        } else {
            this->raiz = aux->getNext();
        }
        aux->setNext(nullptr);
        this->size--;
        return aux;
    }

    bool isEmpty() {
        return this->raiz == nullptr;
    }

    void imprimirLista() {
        Nodo<T> *actual = this->raiz;
        while (actual != nullptr) {
            cout << actual->getValue() << ", ";
            actual = actual->getNext();
        }
        cout << "nullptr" << endl;
    }
};
#endif //LISTAENLAZADA_H
