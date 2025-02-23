//
// Created by ronyrojas on 19/02/25.
//

#ifndef COLA_H
#define COLA_H
#include <iostream>

using namespace std;

template<typename T>
class Cola {
private:
    struct Nodo {
        T dato; // valor del elemento (nodo)
        Nodo *siguiente; // apuntador al siguiente elemento
        Nodo(T nuevoDato) : dato(nuevoDato), siguiente(nullptr) {
        } // constructor con el primer elemento y el siguiente
    };

    Nodo *frente; // apuntador al frente de la cola
    Nodo *final; // apuntador al final de la cola

public:
    Cola(); // constructor de la clase cola

    void encolar(T nuevoDato); // metodo para agregar elementos a la cola
    T desencolar(); // metodo para eliminar elementos de la cola
    T obtenerFrente() const; // metodo para obtener al primer elemento de la cola
    bool estaVacia() const; // metodo que verifica si la cola esta vacia
    void mostrarCola() const; // metodo para mostrar la cola
    Cola<T> mezclarCola(); // metodo para mezclar una cola
    int contarElementos() const;
};

template<typename T>
Cola<T>::Cola() : frente(nullptr), final(nullptr) {
}

template<typename T>
void Cola<T>::encolar(T nuevoDato) {
    Nodo *nuevoNodo = new Nodo(nuevoDato); // creando nuevo nodo con el dato recibido
    if (estaVacia()) // si la cola esta vacia
    {
        frente = nuevoNodo;
        final = nuevoNodo; // el nuevo nodo se convierte en el final y el frente de la cola
    } else // si la cola no esta vacia
    {
        final->siguiente = nuevoNodo; // se actualiza el puntero del final de la cola
        final = nuevoNodo; // actualizando el nodo final con el dato recibido
    }
}

template<typename T>
T Cola<T>::desencolar() {
    if (estaVacia()) {
        throw runtime_error("La cola está vacía"); // si la cola esta vacia arrojamos error
    }

    Nodo *tmp = frente; // guardando el primer nodo
    T dato = tmp->dato; // almacenando el objeto
    frente = frente->siguiente; // cambiando dato de enfrente por el siguiente del frente
    delete tmp; // liberando memoria

    if (frente == nullptr) {
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
    return frente->dato; // regresando el nodo que esta enfrente
}

template<typename T>
bool Cola<T>::estaVacia() const {
    return frente == nullptr;
    // si el nodo de enfrente es igual a null significa que esta vacia la cola y se devuelve un true
}

template<typename T>
void Cola<T>::mostrarCola() const {
    Nodo *actual = frente; // se crea un nodo actual para contener el inicio de la cola
    while (actual) // mientras exista un nodo actual
    {
        cout << actual->dato << " \n"; // Se imprime ese nodo actual
        actual = actual->siguiente; // el nodo actual se actualiza al siguiente nodo de la cola
    }
    cout << endl;
}

template<typename T>
Cola<T> Cola<T>::mezclarCola() {
    int cantidad = 0; //var para contar los elementos de la cola
    Nodo *temporal = frente;
    while (temporal != nullptr) {
        cantidad++;
        temporal = temporal->siguiente;
    }

    T *arreglo = new T[cantidad]; //convirtiendo la cola en un arreglo para una facil manipulacion
    for (int i = 0; i < cantidad; i++) {
        arreglo[i] = obtenerFrente(); // guardando el primer dato
        desencolar(); // eliminando el primer dato
    }

    //mezclando el arreglo con algoritmo fisher-yates
    srand(static_cast<unsigned int>(time(nullptr))); // semilla de aleatoriedad
    for (int i = cantidad - 1; i > 0; i--) {
        int indiceAleatorio = rand() % (i + 1); // generando indice aleatorio

        // moviendo arreglo[i] con arreglo[indiceAleatorio]
        T temp = arreglo[i];
        arreglo[i] = arreglo[indiceAleatorio];
        arreglo[indiceAleatorio] = temp;
    }

    // encolando los elementos mezclados en una nueva cola
    Cola<T> colaMezclada;
    for (int i = 0; i < cantidad; i++) {
        colaMezclada.encolar(arreglo[i]);
    }

    delete[] arreglo;
    return colaMezclada;
}

template<typename T>
int Cola<T>::contarElementos() const {
    int contador = 0;
    Nodo *actual = frente;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}
#endif //COLA_H
