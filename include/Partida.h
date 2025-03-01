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
    Cola<Jugador> *jugadores;
    Pila<Palabra> *palabrasJugadas;
    ListaEnlazada<Jugador> *listaPunteos;
    ListaEnlazada<Palabra> *diccionario;
    ListaEnlazada<Letra> *letrasJugables;
    bool hayPalabra;
    bool hayLetraCentro;
    bool partidaTerminada;
    Jugador jugadorActual;
    Tablero tableroDeJuego;

public:
    Partida();

    ~Partida();

    void iniciarPartida(ListaEnlazada<Palabra> *diccionario);

    void agregarJugadores();

    void generarLetrasJugables();

    void repartirLetras();

    void ordenarLetrasJugables();

    void cambiarTurno();

    void realizarTurno(int opcionTurno);

    void comprobarLetraFormada(ListaEnlazada<Palabra> *diccionario);

    Pila<Palabra> *getPalabrasJugadas();

    ListaEnlazada<Palabra> *getDiccionario();

    Cola<Jugador> *getJugadores();
};
#endif //PARTIDA_H
