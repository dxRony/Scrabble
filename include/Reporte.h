//
// Created by ronyrojas on 19/02/25.
//

#ifndef REPORTE_H
#define REPORTE_H

#include "Pila.h"
#include "ListaEnlazada.h"
#include "Palabra.h"
#include "Jugador.h"

class Reporte
{
private:
    Pila<Palabra> palabrasEncontradas;
    Pila<Palabra> palabrasPerdidas;
    ListaEnlazada<Jugador> listaJugadores;
    ListaEnlazada<int> tiempoPorTurno;

public:
    Reporte();

    //getters
    Pila<Palabra> getPilaPalabrasEncontradas() const;
    Pila<Palabra> getPilaPalabrasPerdidas() const;
    ListaEnlazada<Jugador> getListaJugadores() const;
    ListaEnlazada<int> getListaTiempoPorTurno() const;

};

#endif //REPORTE_H
