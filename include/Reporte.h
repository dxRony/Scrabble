#ifndef REPORTE_H
#define REPORTE_H
#include "Pila.h"
#include "Palabra.h"
#include "ListaEnlazada.h"
#include "Jugador.h"
#include "Cola.h"

class Reporte {
private:
    Pila<Palabra> *palabrasEncontradas;
    Pila<Palabra> *palabrasPerdidas;
    ListaEnlazada<Jugador> *listaJugadores;

public:
    Reporte();

    void actualizarReportes(Pila<Palabra> *palabrasJugadas, ListaEnlazada<Palabra> *diccionario,
                            Cola<Jugador> *jugadores);

    void mostrarPalabrasEncontradas();

    void mostrarPalabrasPerdidas();

    void mostrarListaJugadores();
};

#endif //REPORTE_H
