//
// Created by ronyrojas on 26/02/25.
//
#include "../include/Partida.h"
using namespace std;

Partida::Partida() {
    jugadores = new Cola<Jugador>();
    palabrasJugadas = new Pila<Palabra>();
    listaPunteos = new ListaEnlazada<Jugador>();
    letrasJugables = new ListaEnlazada<Letra>();
    diccionario = nullptr;
    hayPalabra = false;
    hayLetraCentro = false;
}

Partida::~Partida() {
   // delete jugadores;
    //delete palabrasJugadas;
    //delete listaPunteos;
    //delete letrasJugables;
}

void Partida::iniciarPartida(ListaEnlazada<Palabra> *diccionario) {
    this->diccionario = diccionario;
    cout << "\nDiccionario recibido y asignado a la partida." << endl;
    cout << "Palabras en el diccionario:" << endl;
    diccionario->imprimirLista();
    agregarJugadores();


}

void Partida::agregarJugadores() {
    int cantidadJugadores;
    cout << "\nIngrese la cantidad de jugadores (al menos 2): ";
    cin >> cantidadJugadores;

    while (cantidadJugadores < 2) {
        cout << "Debe haber al menos 2 jugadores. Intente nuevamente: ";
        cin >> cantidadJugadores;
    }

    for (int i = 1; i <= cantidadJugadores; i++) {
        string nombreJugador;
        cout << "Ingrese el nombre del jugador " << i << ": ";
        cin >> nombreJugador;

        Jugador nuevoJugador;  // Jugador creado dinámicamente
        nuevoJugador.setNombre(nombreJugador); // Uso de puntero
        jugadores->encolar2(nuevoJugador);       // Se pasa Jugador* como argumento
    }

    cout << "\nJugadores agregados correctamente a la partida.\n" << endl;
    jugadores->mostrarCola();
}


