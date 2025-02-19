//
// Created by ronyrojas on 19/02/25.
//

#ifndef COLA_H
#define COLA_H
#include <iostream>

using namespace std;

template <typename T>
class Cola
{
private:
    struct Nodo
    {
        T dato;                                                    // valor del elemento (nodo)
        Nodo *siguiente;                                           // apuntador al siguiente elemento
        Nodo(T nuevoDato) : dato(nuevoDato), siguiente(nullptr) {} // constructor con el primer elemento y el siguiente
    };

    Nodo *frente; // apuntador al frente de la cola
    Nodo *final;  // apuntador al final de la cola

public:
    Cola(); // constructor de la clase cola

    void encolar(T nuevoDato); // metodo para agregar elementos a la cola
    void desencolar();         // metodo para eliminar elementos de la cola
    T obtenerFrente() const;   // metodo para obtener al primer elemento de la cola
    bool estaVacia() const;    // metodo que verifica si la cola esta vacia
    void mostrarCola() const;  // metodo para mostrar la cola
};

template <typename T>
Cola<T>::Cola() : frente(nullptr), final(nullptr) {}

template <typename T>
void Cola<T>::encolar(T nuevoDato)
{
    Nodo *nuevoNodo = new Nodo(nuevoDato); // creando nuevo nodo con el dato recibido
    if (estaVacia())                       // si la cola esta vacia
    {
        frente = nuevoNodo;
        final = nuevoNodo; // el nuevo nodo se convierte en el final y el frente de la cola
    }
    else // si la cola no esta vacia
    {
        final->siguiente = nuevoNodo; // se actualiza el puntero del final de la cola
        final = nuevoNodo;            // actualizando el nodo final con el dato recibido
    }
}

template <typename T>
void Cola<T>::desencolar()
{
    if (estaVacia()) // si la cola esta vacia no se puede desencola ningun dato de la cola
    {
        cout << "La cola esta vacia\n";
        return;
    }

    Nodo *temp = frente;        // guardando temporalmente el frente de la cola
    frente = frente->siguiente; // el nodo que sigue al frente se convierte en el frente
    delete temp;                // eliminando el dato que estaba en el frente de la cola

    if (frente == nullptr) // si el frente de la cola queda vacio
    {
        final = nullptr; // el final se vuelve vacio (ya no hay nodos en la cola)
    }
}

template <typename T>
T Cola<T>::obtenerFrente() const
{
    if (estaVacia()) // si la cola esta vacia no se puede devolver nada
    {
        throw runtime_error("La cola esta vacia");
        return;
    }
    return frente->dato; // regresando el nodo que esta enfrente
}

template <typename T>
bool Cola<T>::estaVacia() const
{
    return frente == nullptr; // si el nodo de enfrente es igual a null significa que esta vacia la cola y se devuelve un true
}

template <typename T>
void Cola<T>::mostrarCola() const
{
    Nodo *actual = frente; // se crea un nodo actual para contener el inicio de la cola
    while (actual)         // mientras exista un nodo actual
    {
        cout << actual->dato << " "; // Se imprime ese nodo actual
        actual = actual->siguiente;  // el nodo actual se actualiza al siguiente nodo de la cola
    }
    cout << endl;
}
#endif //COLA_H
