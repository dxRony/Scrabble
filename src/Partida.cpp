//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Partida.h"
#include <iostream>

using namespace std;

Partida::Partida() : jugadores(), palabrasJugadas(), listaPunteos(), diccionario(), letrasJugables()
{
    this->hayPalabra = true;
}

// getters
Cola<Jugador> Partida::getColaJugadores() const { return jugadores; }
Pila<Palabra> Partida::getPilaPalabrasJugadas() const { return palabrasJugadas; }
ListaEnlazada<Jugador> Partida::getListaPunteos() const { return listaPunteos; }
ListaEnlazada<Palabra> Partida::getListaDiccionario() const { return diccionario; }
ListaEnlazada<Letra> Partida::getListaLetrasJugables() const { return letrasJugables; }

bool Partida::getHayPalabra() const { return hayPalabra; }

// setters
void Partida::setHayPalabra(bool nuevaHayPalabra)
{
    hayPalabra = nuevaHayPalabra;
}
