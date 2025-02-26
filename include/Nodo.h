//
// Created by ronyrojas on 26/02/25.
//

#ifndef NODO_H
#define NODO_H
template <class T> class Nodo {

private:
    T *data;
    Nodo *next;

public:
    explicit Nodo(const T &value) : data(new T(value)), next(nullptr) {}

    T *getData() {
        return this->data;
    }

    void setData(T *value) {
        delete this->data;          // Libera el dato actual
        this->data = new T(value);  // Asigna el nuevo valor
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
