//
// Created by ronyrojas on 19/02/25.
//

#ifndef TABLERO_H
#define TABLERO_H
#include "Letra.h"
#include "ListaEnlazada.h"
#include "Palabra.h"


class Tablero {
private:
    Letra casillas[15][15];
    bool hayLetraCentro;
    void comprobarPalabraFormada(ListaEnlazada<Palabra> diccionario);

public:
    Tablero();

    void generarTablero();

    void imprimirTablero() const;
    
    void colocarLetra(Letra letra, int fila, int columna, ListaEnlazada<Palabra> diccionario);

    

    bool getHayLetraCentro() const;

    void setHayLetraCentro(bool hayLetra);

};

#endif //TABLERO_H
