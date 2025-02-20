//
// Created by ronyrojas on 19/02/25.
//
#ifndef PARTIDA_H
#define PARTIDA_H

#include "ListaEnlazada.h"
#include "Cola.h"
#include "Pila.h"
#include "Jugador.h"
#include "Palabra.h"

class Partida
{
private:
    Cola<Jugador> jugadores;
    Pila<Palabra> palabrasJugadas;
    ListaEnlazada<Jugador> listaPunteos;
    ListaEnlazada<Palabra> diccionario;
    ListaEnlazada<Letra> letrasJugables;
    //pendiente array de Letras
    bool hayPalabra;

public:
    Partida();

    void iniciarPartida(ListaEnlazada<Palabra> diccionario);
    void registrarJugadores();
    ListaEnlazada<Letra> generarLetrasJugables(ListaEnlazada<Palabra> &diccionario);
    void repartirLetras();

    //getters
    Cola<Jugador> getColaJugadores() const;
    Pila<Palabra> getPilaPalabrasJugadas() const;
    ListaEnlazada<Jugador> getListaPunteos() const;
    ListaEnlazada<Palabra> getListaDiccionario() const;
    ListaEnlazada<Letra> getListaLetrasJugables() const;
    //pendiente getterTablero
    bool getHayPalabra() const;

    //setters
    void setHayPalabra(bool hayPalabra);

};

#endif //PARTIDA_H
