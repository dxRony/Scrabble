//
// Created by ronyrojas on 24/02/25.
//

#ifndef NODO_H
#define NODO_H
template<typename T>
struct Nodo {
    T dato;               // Apuntador al dato
    Nodo<T> *siguiente;    // Apuntador al siguiente nodo

    explicit Nodo(T *nuevoDato) : dato(nuevoDato), siguiente(nullptr) {} // Constructor
    ~Nodo() { delete dato; }                                             // Destructor
};
#endif //NODO_H
