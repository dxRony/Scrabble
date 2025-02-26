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
#include "Tablero.h"

class Partida {
private:
    Cola<Jugador*> *jugadores;
    Pila<Palabra*> *palabrasJugadas;
    ListaEnlazada<Jugador*> *listaPunteos;
    ListaEnlazada<Palabra> *diccionario;
    ListaEnlazada<Letra*> *letrasJugables;
    bool hayPalabra;
    bool hayLetraCentro;
    Jugador *jugadorActual;
    Tablero *tableroDeJuego;

public:
    Partida();

    ~Partida();

    void iniciarPartida(ListaEnlazada<Palabra> *diccionario);

    void registrarJugadores();

    ListaEnlazada<Letra*> *generarLetrasJugables(ListaEnlazada<Palabra> *diccionario);

    void repartirLetras();

    void ordenarLetrasJugadores();

    //getters
    Cola<Jugador*> *getColaJugadores() const;

    Pila<Palabra*> *getPilaPalabrasJugadas() const;

    ListaEnlazada<Jugador*> *getListaPunteos() const;

    ListaEnlazada<Palabra> *getListaDiccionario() const;

    ListaEnlazada<Letra*> *getListaLetrasJugables() const;

    Jugador *cambiarTurno();

    void realizarTurno(int opcionTurno);

    bool getHayPalabra() const;

    bool getHayLetraCentro() const;

    //setters
    void setHayPalabra(bool hayPalabra);

    void setHayLetraCentro(bool hayLetraCentro);
};

#endif //PARTIDA_H
