//
// Created by ronyrojas on 19/02/25.
//

#ifndef COLA_H
#define COLA_H
#include <iostream>
#include "Nodo.h"
using namespace std;

template<typename T>
class Cola {
private:
    Nodo<T> *frente; // apuntador al frente de la cola
    Nodo<T> *final; // apuntador al final de la cola

public:
    Cola(); // constructor de la clase cola
    ~Cola(); //destructir

    void encolar(const T &nuevoDato); // metodo para agregar elementos a la cola
    T desencolar(); // metodo para eliminar elementos de la cola
    T obtenerFrente() const; // metodo para obtener al primer elemento de la cola
    bool estaVacia() const; // metodo que verifica si la cola esta vacia
    void mostrarCola() const; // metodo para mostrar la cola
    Cola<T> mezclarCola(); // metodo para mezclar una cola
    int contarElementos() const;
};

template<typename T>
Cola<T>::Cola() : frente(nullptr), final(nullptr) {
    //inicia los punteros con nullptr
}


template<typename T>
Cola<T>::~Cola() {
    // libera la memoria de todos los nodos
    while (!estaVacia()) {
        desencolar();
    }
}

template<typename T>
void Cola<T>::encolar(const T &nuevoDato) {
    Nodo<T> *nuevoNodo = new Nodo<T>(nuevoDato); // creando nuevo nodo con el dato
    if (estaVacia()) {
        // si la cola esta vacia
        frente = nuevoNodo;
        final = nuevoNodo; // el nuevo nodo se convierte en el final y el frente de la cola
    } else {
        // si la cola no esta vacia
        final->siguiente = nuevoNodo; // se actualiza el puntero del final de la cola
        final = nuevoNodo; // actualizando el nodo final con el dato recibido
    }
}

template<typename T>
T Cola<T>::desencolar() {
    if (estaVacia()) {
        throw runtime_error("La cola está vacía"); // si la cola esta vacia arrojamos error
    }

    Nodo<T> *tmp = frente; // creando nodo temporal
    T dato = (frente->dato); // almacenando el dato
    frente = frente->siguiente; // cambiando dato de enfrente por el siguiente
    delete tmp; // liberando memoria

    if (!frente) {
        final = nullptr; //si ya no hay dato de enfrente, no hay dato al final
    }
    return dato; // devolviendo el dato
}

template<typename T>
T Cola<T>::obtenerFrente() const {
    if (estaVacia()) // si la cola esta vacia no se puede devolver nada
    {
        throw runtime_error("La cola esta vacia");
    }
    return *(frente->dato); // regresando el nodo que esta enfrente
}

template<typename T>
bool Cola<T>::estaVacia() const {
    return frente == nullptr;
    // si el nodo de enfrente es igual a null significa que esta vacia la cola y se devuelve un true
}

template<typename T>
void Cola<T>::mostrarCola() const {
    Nodo<T> *actual = frente; // se crea un nodo actual para contener el inicio de la cola
    while (actual) {
        // mientras exista un nodo actual
        cout << actual->dato << " \n"; // Se imprime ese nodo actual
        actual = actual->siguiente; // el nodo actual se actualiza al siguiente nodo de la cola
    }
    cout << endl;
}

template<typename T>
Cola<T> Cola<T>::mezclarCola() {
    int cantidad = contarElementos(); //var para almacenar los elementos de la cola
    if (cantidad == 0) {
        return *this;
    }

    T **arreglo = new T *[cantidad]; //convirtiendo la cola en un arreglo para una facil manipulacion
    Nodo<T> *actual = frente;
    for (int i = 0; i < cantidad; i++) {
        arreglo[i] = new T(actual->dato); // guardando el primer dato
        actual = actual->siguiente;
    }

    //mezclando el arreglo con algoritmo fisher-yates
    srand(static_cast<unsigned int>(time(nullptr))); // semilla de aleatoriedad
    for (int i = cantidad - 1; i > 0; i--) {
        int indiceAleatorio = rand() % (i + 1); // generando indice aleatorio
        swap(arreglo[i], arreglo[indiceAleatorio]);
    }
    // encolando los elementos mezclados en una nueva cola
    Cola<T> colaMezclada;
    for (int i = 0; i < cantidad; i++) {
        colaMezclada.encolar(*(arreglo[i]));
        delete arreglo[i]; //liberando memora de cada dato ya manipulado
    }
    delete[] arreglo; //liberando memoria del arreglo vacio
    return colaMezclada;
}

template<typename T>
int Cola<T>::contarElementos() const {
    int contador = 0;
    Nodo<T> *actual = frente;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}
#endif //COLA_H
