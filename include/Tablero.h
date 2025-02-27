//
// Created by ronyrojas on 26/02/25.
//

#ifndef TABLERO_H
#define TABLERO_H
#include "Letra.h"

class Tablero {
private:
    Letra *casillas[15][15];
    bool hayLetraCentro;

public:
    Tablero();

    void generarTablero();

    void imprimirTablero()const;
};

#endif //TABLERO_H
