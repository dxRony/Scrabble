//
// Created by ronyrojas on 26/02/25.
//

#ifndef NODO_H
#define NODO_H

template<class T>
class Nodo {
private:
    T *data; //puntero dato almacenado
    Nodo *next; //putero a el siguiente nodo

public:
    //constructor con data y next como null
    explicit Nodo(const T &value) : data(new T(value)), next(nullptr) {
    }

    T *getData() {
        //devuelve puntero del dato
        return this->data;
    }

    void setData(T *value) {
        delete this->data; // elimina el dato actual
        this->data = value; // asigna nuevoPuntero
    }

    Nodo *getNext() {
        //devuelve el puntero del nodo siguiente
        return this->next;
    }

    void setNext(Nodo *next) {
        //manda el puntero del nodo siguiente
        this->next = next;
    }

    T getValue() {
        //quita referencia del puntero y devuelve el valor unicamente
        return *this->data;
    }

    void setValue(T value) {
        //enviando nuevo valor al dato
        delete this->data;
        this->data = new T(value);
    }
};
#endif //NODO_H
