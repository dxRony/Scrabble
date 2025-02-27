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

    Letra* obtenerLetra(int fila, int columna)const;

    bool colocarLetra(int fila, int columna, Letra* letraAColocar);

    bool verificarPalabraTablero(const string &palabra);

    bool verificarPalabraFormada(int fila, int columna, const string &palabra);

    Letra* obtenerLetraTablero(char letraChar);
};

#endif //TABLERO_H
