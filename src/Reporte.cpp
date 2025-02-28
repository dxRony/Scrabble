//
// Created by ronyrojas on 27/02/25.
//
#include "../include/Reporte.h"

using namespace std;

Reporte::Reporte() {
    palabrasEncontradas = new Pila<Palabra>();
    palabrasPerdidas = new Pila<Palabra>();
    listaJugadores = new ListaEnlazada<Jugador>();
}

void Reporte::actualizarReportes(Pila<Palabra> *palabrasJugadas, ListaEnlazada<Palabra> *diccionario,
                                 Cola<Jugador> *jugadores) {
    //reseteando estructuras de la partida anterior (si es que hay)
    palabrasEncontradas = new Pila<Palabra>();
    palabrasPerdidas = new Pila<Palabra>();
    listaJugadores = new ListaEnlazada<Jugador>();

    // insertando las plabras jugadas una por una de la partida anterior
    while (!palabrasJugadas->isEmpty()) {
        palabrasEncontradas->push(*palabrasJugadas->pop());
    }
    // insertando palabras no encontradas de la partida anterior
    for (int i = 0; i < diccionario->getTamano(); i++) {
        palabrasPerdidas->push(*diccionario->obtenerDatoEnPosicion(i));
    }
    // desencolando a los jugadores para agregarlos a la lista de jugadores
    int numJugadores = jugadores->obtenerTamano();
    for (int i = 0; i < numJugadores; i++) {
        Jugador *jugador = jugadores->desencolar();
        listaJugadores->insertar(*jugador);
        jugadores->encolar(jugador); // encolandolos otra vez para no corromper los datos
    }
}

void Reporte::mostrarPalabrasEncontradas() {
    cout << "\n*********** Palabras Encontradas ***********" << endl;
    if (palabrasEncontradas->isEmpty()) {
        cout << "No hay palabras encontradas en la anterior partida" << endl;
    } else {
        palabrasEncontradas->mostrarPila();
    }
}

void Reporte::mostrarPalabrasPerdidas() {
    cout << "\n*********** Palabras No Encontradas ***********" << endl;
    if (palabrasPerdidas->isEmpty()) {
        cout << "No hay palabras perdidas en la anterior partida" << endl;
    } else {
        palabrasPerdidas->mostrarPila();
    }
}

void Reporte::mostrarListaJugadores() {
    cout << "\n*********** Lista de Jugadores ***********" << endl;
    if (listaJugadores->isEmpty()) {
        cout << "No hay jugadores registrados en la anterior partida" << endl;
    } else {
        listaJugadores->imprimirLista2();
    }
}
