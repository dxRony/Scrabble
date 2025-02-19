//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Reporte.h"
#include <iostream>

using namespace std;

Reporte::Reporte() : palabrasEncontradas(), palabrasPerdidas(), listaJugadores(), tiempoPorTurno()
{
}

// getters
Pila<Palabra> Reporte::getPilaPalabrasEncontradas() const { return palabrasEncontradas; }
Pila<Palabra> Reporte::getPilaPalabrasPerdidas() const { return palabrasPerdidas; }
ListaEnlazada<Jugador> Reporte::getListaJugadores() const { return listaJugadores; }
ListaEnlazada<int> Reporte::getListaTiempoPorTurno() const { return tiempoPorTurno; }