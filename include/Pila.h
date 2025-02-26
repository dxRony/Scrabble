//
// Created by ronyrojas on 19/02/25.
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
    Nodo<T> *cima; // apuntador al primer elemento de la pila

public:
    Pila(); // constructor de la pila
    ~Pila(); // destructir de la pila

    void push(const T &nuevoDato); // metodo que agrega el nodo a la cima de la pila
    void pop(); // metodo que elimina el nodo en la cima de la pila
    T top() const; // metodo que devuelve el nodo en la cima sin removerlo
    bool estaVacia() const; // metodo para verificar si la pila esta vacia
    void mostrarPila() const; // metodo para mostrar la pila
};

template<typename T>
Pila<T>::Pila() {
    cima = nullptr;
}

template<typename T>
Pila<T>::~Pila() {
    //libera todos los nodos
    while (!estaVacia()) {
        pop();
    }
}

template<typename T>
void Pila<T>::push(const T &nuevoDato) {
    Nodo<T> *nuevoNodo = new Nodo<T>(new T(nuevoDato)); //creando el nuevo nodo con el contenido recibido
    nuevoNodo->siguiente = cima; // actualizando el puntero de la cima
    cima = nuevoNodo; // actualizando el nodo que esta en la cima
}

template<typename T>
void Pila<T>::pop() {
    if (estaVacia()) {
        //si la pila esta vacia
        cout << "La pila esta vacia\n";
        return; //no se puede eliminar la cima
    }
    Nodo<T> *temp = cima; // guardando el contenido del nodo de la cima temporalmente
    cima = cima->siguiente; // actualizando la cima al nodo siguiente de la cima actual
    delete temp; // eliminamos la antigua cima de la pila
}

template<typename T>
T Pila<T>::top() const {
    if (estaVacia()) {
        //si la pila esta vacia no se puede obtener la cima
        throw runtime_error("La pila esta vacia");
    }
    return *(cima->dato); //retornando el elemento que esta en la cima sin eliminarlo
}

template<typename T>
bool Pila<T>::estaVacia() const {
    return cima == nullptr; //devuelve true si la pila esta vacia
}

template<typename T>
void Pila<T>::mostrarPila() const {
    Nodo<T> *actual = cima; //creando nodo actual para ir guardando los nodos
    while (actual) {
        cout << *(actual->dato) << " "; //guardando el nodo actual mientras exista
        actual = actual->siguiente; //actualizando el nodo actual para recorrer toda la pila
    } //ACTUAL SE CONVIERTE EN EL SIGUIENTE DEL ACTUAL
    cout << endl;
}
#endif //PILA_H
