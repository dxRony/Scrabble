//
// Created by ronyrojas on 24/02/25.
//

#ifndef NODO_H
#define NODO_H
template <class T> class Nodo {

private:
    T *data;
    Nodo *next;

public:
    Nodo(T *value) {
        this->data = value;
        this->next = nullptr;
    }

    Nodo(T value) {
        this->data = new T(value);
        this->next = nullptr;
    }

    T *getData() {
        return this->data;
    }

    void setData(T *value) {
        this->data = value;
    }

    Nodo *getNext() {
        return this->next;
    }

    void setNext(Nodo *next) {
        this->next = next;
    }

    T getValue() {
        return *this->data;
    }

    void setValue(T value) {
        this->data = new T(value);
    }

};
#endif //NODO_H
