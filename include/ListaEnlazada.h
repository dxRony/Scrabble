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
    Nodo<T> *cabeza; //apuntador al primer nodo de la lista
    int tamano; //tamaño de la lista

public:
    ListaEnlazada() {
        //iniciando lista vacia
        this->cabeza = nullptr;
        this->tamano = 0;
    }

    Nodo<T> *getCabeza() {
        //devuelve el apuntador de la cabez
        return this->cabeza;
    }

    void setCabeza(Nodo<T> *cabeza) {
        //actualiza el apuntador de la cabeza de la lista
        this->cabeza = cabeza;
    }

    int getTamano() {
        return this->tamano;
    }

    void setTamano(int tamano) {
        this->tamano = tamano;
    }

    Nodo<T> *getElement(int index) {
        if (index < 0 || index >= this->tamano) return nullptr;

        if (index == 0) return this->cabeza;

        int contadorAux = 0;
        Nodo<T> *aux = this->cabeza;
        //recorre la lista hasta llegar al indice requerido y devuelve el nodo
        while (contadorAux < index) {
            aux = aux->getNext();
            contadorAux++;
        }
        return aux;
    }

    void insertar(T value) {
        //inserta un nuevo nodo al final de la lista
        auto *nuevoNodo = new Nodo<T>(value);
        if (this->cabeza == nullptr) {
            this->cabeza = nuevoNodo;
            tamano++;
            return;
        }
        Nodo<T> *aux = this->cabeza;
        //mientras haya un siguiente, se actualiza el aux
        while (aux->getNext() != nullptr) {
            aux = aux->getNext();
        }
        aux->setNext(nuevoNodo);
        tamano++;
    }

    void insertar2(T *value) {
        //viendo que el puntero no sea nulo
        if (value == nullptr) {
            return;
        }
        // creando nuevo nodo
        auto *nuevoNodo = new Nodo<T>(*value);
        if (this->cabeza == nullptr) {
            this->cabeza = nuevoNodo;
            tamano++;
            return;
        }
        Nodo<T> *aux = this->cabeza;
        while (aux->getNext() != nullptr) {
            aux = aux->getNext();
        }
        aux->setNext(nuevoNodo);
        tamano++;
    }

    T *eliminar(T *value) {
        //elimina el nodo dado el valor
        Nodo<T> *aux = this->cabeza;
        Nodo<T> *previo = nullptr; //guarda el nodo anterior para conectarlo al siguiente del dato a eliminar
        while (aux != nullptr && aux->getData() != value) {
            previo = aux;
            aux = aux->getNext();
        }
        if (aux == nullptr) {
            return nullptr;
        }
        if (previo != nullptr) {
            previo->setNext(aux->getNext());
        } else {
            this->cabeza = aux->getNext();
        }
        aux->setNext(nullptr);
        tamano--;
        return aux->getData();
    }

    T *eliminar2(int indice) {
        //elimina el dato y lo devuelve por el indice recibido
        if (indice < 0 || indice >= tamano) {
            return nullptr; // Índice no válido
        }
        Nodo<T> *aux = cabeza;
        Nodo<T> *previo = nullptr;

        for (int i = 0; i < indice; i++) {
            previo = aux;
            aux = aux->getNext();
        }
        if (previo != nullptr) {
            previo->setNext(aux->getNext());
        } else {
            cabeza = aux->getNext();
        }
        T *dato = aux->getData();
        delete aux;
        tamano--;
        return dato;
    }

    Nodo<T> *eliminarPorIndice(int index) {
        //elimina y devuelve el nodo
        Nodo<T> *aux = this->cabeza;
        Nodo<T> *previo = nullptr;
        for (int i = 0; i < index; i++) {
            previo = aux;
            aux = aux->getNext();
        }
        if (previo != nullptr) {
            previo->setNext(aux->getNext());
        } else {
            this->cabeza = aux->getNext();
        }
        aux->setNext(nullptr);
        tamano--;
        return aux;
    }

    bool isEmpty() {
        return this->cabeza == nullptr;
    }

    void imprimirLista() {
        Nodo<T> *actual = this->cabeza;
        while (actual != nullptr) {
            cout << actual->getValue() << ", ";
            actual = actual->getNext();
        }
        cout << "nullptr" << endl;
    }

    T *obtenerDatoEnPosicion(int posicion) {
        //devuelve el dato, sin eliminarlo
        if (posicion < 0 || posicion >= this->tamano) {
            throw out_of_range("Posición fuera de rango");
        }
        Nodo<T> *nodo = this->getElement(posicion);
        return nodo->getData();
    }
};
#endif //LISTAENLAZADA_H
