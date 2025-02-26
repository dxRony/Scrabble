//
// Created by ronyrojas on 19/02/25.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <iostream>
#include <stdexcept>
#include "Nodo.h"

using namespace std;

template<typename T>
class ListaEnlazada {
private:
    Nodo<T> *cabeza; //apuntador al primer nodo (cabeza) de la lista

public:
    ListaEnlazada(); //constructor
    ~ListaEnlazada(); //destructor

    void agregarInicio(const T &nuevoDato); //agrega un dato al inicio
    void agregarFinal(const T &nuevoDato); //agrega un dato al final
    void eliminar(const T &valor); //elimina el primer nodo con el valor dado
    Nodo<T> *obtenerCabeza(); //devuelve el apuntador de la cabeza
    void setCabeza(Nodo<T> *nuevaCabeza); //modifica la cabea de la lista
    bool estaVacia() const; //indica si la lista esta vacia
    void mostrarLista() const; //muestra todos los elementos de la lista
    int contarElementos() const; //cuenta los elementos de la lista
    T obtenerYEliminar(int indice); //obtiene y elimina el dato segun el indice
};

template<typename T>
ListaEnlazada<T>::ListaEnlazada() {
    // constructor
    cabeza = nullptr; // la lista empieza con la cabeza nula (no hay datos)
}

// libera todos los nodos
template<typename T>
ListaEnlazada<T>::~ListaEnlazada() {
    while (!estaVacia()) {
        obtenerYEliminar(0); // elimina la cabeza
    }
}

template<typename T>
void ListaEnlazada<T>::agregarInicio(const T &nuevoDato) {
    auto *nuevoNodo = new Nodo<T>(new T(nuevoDato)); // creando nuevo dato
    nuevoNodo->siguiente = cabeza; // el nuevo nodo apunta a la cabeza
    cabeza = nuevoNodo; // el nuevo nodo se convierte en la cabeza
}

template<typename T>
void ListaEnlazada<T>::agregarFinal(const T &nuevoDato) {
    auto *nuevoNodo = new Nodo<T>(new T(nuevoDato)); //creando nodo que contenga al nuevo elemento
    if (estaVacia()) {
        cabeza = nuevoNodo; //si la lista esta vacia, el nuevoNodo sera la cabeza
    } else {
        Nodo<T> *actual = cabeza; //creando nodo conteniendo a la cabeza
        while (actual->siguiente) {
            //mientras el nodo actual tenga siguiente
            actual = actual->siguiente; //se actualiza el nodo actual al siguiente
        }
        actual->siguiente = nuevoNodo; //cuando ya no haya siguiente, el siguiente del actual sera el nuevo nodo
    }
}

template<typename T>
void ListaEnlazada<T>::eliminar(const T &valor) {
    Nodo<T> *actual = cabeza; // guardando la cabeza de la lista
    Nodo<T> *previo = nullptr; // guardando el nodo anterior

    while (actual) {
        // mientras haya un nodo actual
        if (*(actual->dato) == valor) {
            // si el nodo actual es el nodo a eliminar
            if (previo) {
                // si hay un nodo previo al actual
                previo->siguiente = actual->siguiente;
                // el siguiente del previo se convierte en el siguiente del actual
            } else {
                // si no hay un nodo previo
                cabeza = actual->siguiente; // la cabeza se convierte en el siguiente del actual
            }
            delete actual; // se borra el dato actual (el valor a encontrar)
            return; // termina el loop
        }
        previo = actual; // se guarda el previo para buscar el siguiente elemento
        actual = actual->siguiente; // en el actual se guarda el elemento siguiente
    }
}

template<typename T>
Nodo<T> *ListaEnlazada<T>::obtenerCabeza() {
    return cabeza;
}

template<typename T>
void ListaEnlazada<T>::setCabeza(Nodo<T> *nuevaCabeza) {
    cabeza = nuevaCabeza;
}

template<typename T>
bool ListaEnlazada<T>::estaVacia() const {
    return cabeza == nullptr;
}

template<typename T>
void ListaEnlazada<T>::mostrarLista() const {
    Nodo<T> *actual = cabeza; //obteniendo cabeza
    while (actual) {
        //mientras haya actual
        cout << actual->dato << ", "; //imprimiendo dato actual
        actual = actual->siguiente; //avanzando al siguiente dato
    }
    cout << endl;
}

template<typename T>
int ListaEnlazada<T>::contarElementos() const {
    int contador = 0;
    Nodo<T> *actual = cabeza; //guardando primer elemento
    while (actual) {
        contador++; //aumentando contador
        actual = actual->siguiente; //avanzando de dato
    }
    return contador;
}

template<typename T>
T ListaEnlazada<T>::obtenerYEliminar(int indice) {
    if (estaVacia()) {
        throw out_of_range("La lista está vacía.");
    }
    if (indice < 0 || indice >= contarElementos()) {
        throw out_of_range("Índice fuera de rango.");
    }

    Nodo<T> *actual = cabeza; //guardando cabeza
    Nodo<T> *previo = nullptr; //guardando previo

    for (int i = 0; i < indice && actual!=nullptr; i++) {
        //avanzando de dato hasta llegar al solicitado
        previo = actual;
        actual = actual->siguiente;
    }

    T datoADevolver = actual->dato; // guardando dato solicitado

    if (previo) {
        //si tiene previo
        previo->siguiente = actual->siguiente; //se actualiza el dato
    } else {
        // si no tiene previo (es la cabeza)
        cabeza = actual->siguiente;
    }
    delete actual;
    return datoADevolver;
}
#endif //LISTAENLAZADA_H
