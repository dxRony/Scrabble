//
// Created by ronyrojas on 19/02/25.
//

#ifndef PILA_H
#define PILA_H


#include <iostream>
using namespace std;

template<typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo *siguiente;

        Nodo(T nuevoDato) : dato(nuevoDato), siguiente(nullptr) {
        }
    };

    Nodo *cima; // apuntador al primer elemento de la pila

public:
    Pila(); // constructor

    void push(T nuevoDato); // metodo que agrega el nodo a la cima de la pila
    void pop(); // metodo que elimina el nodo en la cima de la pila
    T top() const; // metodo que devuelve el nodo en la cima sin removerlo
    bool estaVacia() const; // metodo para verificar si la pila esta vacia
    void mostrarPila() const; // metodo para mostrar la pila
};

template<typename T>
Pila<T>::Pila() : cima(nullptr) {
}

template<typename T>
void Pila<T>::push(T nuevoDato) {
    Nodo *nuevoNodo = new Nodo(nuevoDato); //creando el nuevo nodo con el contenido recibido
    nuevoNodo->siguiente = cima; // actualizando el puntero de la cima
    cima = nuevoNodo; // actualizando el nodo que esta en la cima
}

template<typename T>
void Pila<T>::pop() {
    if (estaVacia()) //si la pila esta vacia
    {
        cout << "La pila esta vacia\n";
        return; //no se puede eliminar la cima
    }

    Nodo *temp = cima; // guardando el contenido del nodo de la cima temporalmente
    cima = cima->siguiente; // actualizando la cima al nodo siguiente de la cima actual
    delete temp; // eliminamos la antigua cima de la pila
}

template<typename T>
T Pila<T>::top() const {
    if (estaVacia()) //si la pila esta vacia no se puede obtener la cima
    {
        throw runtime_error("La pila esta vacia");
    }
    return cima->dato; //retornando el elemento que esta en la cima sin eliminarlo
}

template<typename T>
bool Pila<T>::estaVacia() const {
    return cima == nullptr; //devuelve true si la pila esta vacia
}

template<typename T>
void Pila<T>::mostrarPila() const {
    Nodo *actual = cima; //creando nodo actual para ir guardando los nodos
    while (actual) {
        cout << actual->dato << " "; //guardando el nodo actual mientras exista
        actual = actual->siguiente; //actualizando el nodo actual para recorrer toda la pila
    } //ACTUAL SE CONVIERTE EN EL SIGUIENTE DEL ACTUAL
    cout << endl;
}

#endif //PILA_H
