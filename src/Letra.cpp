//
// Created by ronyrojas on 26/02/25.
//
#include "../include/Letra.h"
#include <iostream>

using namespace std;

Letra::Letra() {
    this->letra = ' ';
    this->punteo = 0;
}

// getters
char Letra::getLetra() const {
    return letra;
}

int Letra::getPunteo() const {
    return punteo;
}

//setters
void Letra::setLetra(char letra) {
    this->letra = letra;
}

void Letra::setPunteo(int punteo) {
    this->punteo = punteo;
}

// sobrecarga del operador "<<"
ostream &operator<<(ostream &os, const Letra &l) {
    os << "Letra: " << l.getLetra() << ", Punteo: " << l.getPunteo();
    return os;
}
