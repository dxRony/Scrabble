//
// Created by ronyrojas on 19/02/25.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <iostream>
using namespace std;

template<typename T> // indica que es una estrucutura generica
struct Nodo {
    T dato; // valor del nodo
    Nodo *siguiente; // apuntador al siguiente dato

    Nodo(T nuevoDato) : dato(nuevoDato), siguiente(nullptr) {
    } // constructor con el primero dato y nullptr (siguiente nodo)
};

template<typename T> // indica que es una clase generica
class ListaEnlazada {
private:
    Nodo<T> *cabeza; // puntero al 1er nodo de la lista

public:
    ListaEnlazada();

    void agregarInicio(T nuevoDato);

    void agregarFinal(T nuevoDato);

    Nodo<T> *obtenerCabeza() const;

    void eliminar(T valor);

    void mostrarLista() const;

    int contarElementos() const;

    void setCabeza(Nodo<T> *cabeza);

    bool estaVacia() const;

    T obtenerYEliminar(int indice);
};

template<typename T>
ListaEnlazada<T>::ListaEnlazada() // constructor
{
    cabeza = nullptr; // la lista empieza con la cabeza nula (no hay datos)
}

template<typename T>
void ListaEnlazada<T>::agregarInicio(T nuevoDato) {
    Nodo<T> *nuevoNodo = new Nodo<T>(nuevoDato); // creando nuevo dato
    nuevoNodo->siguiente = cabeza; // el nuevo nodo apunta a la cabeza
    cabeza = nuevoNodo; // el nuevo nodo se convierte en la cabeza
}

template<typename T>
void ListaEnlazada<T>::agregarFinal(T nuevoDato) {
    Nodo<T> *nuevoNodo = new Nodo<T>(nuevoDato); //creando nodo que contenga al nuevo elemento
    if (!cabeza) {
        cabeza = nuevoNodo; //si no hay cabeza de la lista, sera el nuevo nodo
    } else {
        Nodo<T> *actual = cabeza; //creando nodo conteniendo a la cabeza
        while (actual->siguiente) //mientras el nodo actual tenga siguiente
        {
            actual = actual->siguiente; //se actualiza el nodo actual al siguiente
        }
        actual->siguiente = nuevoNodo; //cuando ya no haya siguiente, el siguiente del actual sera el nuevo nodo
    }
}

template<typename T>
void ListaEnlazada<T>::eliminar(T valor) {
    Nodo<T> *actual = cabeza; // guardando la cabeza de la lista
    Nodo<T> *previo = nullptr; // guardando el nodo anterior

    while (actual) // mientras haya un nodo actual
    {
        if (actual->dato == valor) // si el nodo actual es el nodo a eliminar
        {
            if (previo) // si hay un nodo previo al actual
            {
                previo->siguiente = actual->siguiente;
                // el siguiente del previo se convierte en el siguiente del actual
            } else // si no hay un nodo previo
            {
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
Nodo<T> *ListaEnlazada<T>::obtenerCabeza() const {
    if (cabeza) {
        return cabeza;
    }
    return nullptr;
}

template<typename T>
void ListaEnlazada<T>::mostrarLista() const {
    Nodo<T> *actual = cabeza; // en el nodo actual guardamos la cabeza (inicio de la lista)

    while (actual) {
        // mientras exista un nodo actual
        cout << actual->dato << ", "; // imprimimos el dato actual
        actual = actual->siguiente; // el nodo actual se convierte en el siguiente del actual
    }
    cout << endl; // imprimiendo salto de linea cuando no hayan mas elementos
}

template<typename T>
int ListaEnlazada<T>::contarElementos() const {
    int contador = 0;
    Nodo<T> *actual = cabeza; // guardando la cabeza de la lista

    while (actual != nullptr) {
        contador++; // sumando cada nodo
        actual = actual->siguiente; // pasando al siguiente nodo
    }
    return contador;
}

template<typename T>
void ListaEnlazada<T>::setCabeza(Nodo<T> *nuevoCabeza) {
    cabeza = nuevoCabeza;
}

template<typename T>
bool ListaEnlazada<T>::estaVacia() const {
    return cabeza == nullptr;   //devuelve true si la lista esta vacia
}

template<typename T>
T ListaEnlazada<T>::obtenerYEliminar(int indice) {
    if (estaVacia()) {
        throw out_of_range("La lista está vacía.");
    }

    if (indice < 0 || indice >= contarElementos()) {
        throw out_of_range("Índice fuera de rango.");
    }

    Nodo<T> *actual = cabeza;
    Nodo<T> *previo = nullptr;
    int contador = 0;

    while (actual != nullptr && contador < indice) {
        previo = actual;
        actual = actual->siguiente;
        contador++;
    }

    T datoADevolver = actual->dato;  // Guardamos el dato antes de eliminar

    // Si el nodo a eliminar es la cabeza
    if (previo == nullptr) {
        cabeza = actual->siguiente;
    } else {
        previo->siguiente = actual->siguiente;
    }

    delete actual; // Liberamos la memoria del nodo eliminado
    return datoADevolver; // Retornamos el dato eliminado
}
#endif //LISTAENLAZADA_H
