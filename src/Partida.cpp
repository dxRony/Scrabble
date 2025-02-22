//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Partida.h"
#include <iostream>

using namespace std;

Partida::Partida() : jugadores(), palabrasJugadas(), listaPunteos(), diccionario(), letrasJugables() {
    this->hayPalabra = true;
}

void Partida::iniciarPartida(ListaEnlazada<Palabra> diccionario) {
    this->registrarJugadores();
    jugadores = jugadores.mezclarCola();
    this->generarLetrasJugables(diccionario);
    cout << "Letras a repartir entre los jugadores:" << endl;
    letrasJugables.mostrarLista();
    cout << "Repartiendo letras (fichas) entre todos los jugadores..." << endl;
    this->repartirLetras();
    cout << "Generando turnos aleatorios..." << endl;
    cout << "Ornden de los turnos para la partida: " << endl;
    jugadores.mostrarCola();
    cout << "Todo listo para iniciar" << endl;
}

void Partida::registrarJugadores() {
    int cantidadJugadores = 0;
    cout << "Ingresa el numero de jugadores que tendra la partida..." << endl;
    cin >> cantidadJugadores;

    while (cantidadJugadores < 2) {
        cout << "Debe haber minimo 2 jugadores en la partida *_*" << endl;
        cout << "\nIngresa el numero de jugadores que tendra la partida..." << endl;
        cin >> cantidadJugadores;
    }

    for (int i = 0; i < cantidadJugadores; i++) {
        string nombre;
        cout << "Ingresa el nombre del jugador " << i + 1 << ": ";
        cin >> nombre;

        Jugador jugador;
        jugador.setNombre(nombre);
        jugador.setPuntuacion(0);
        jugador.setCantidadTurnos(0);
        jugador.setTiempoJugado(0);
        jugadores.encolar(jugador); // encolando al jugador
    }
    cout << "Jugadores: " << endl;
    jugadores.mostrarCola();
}

ListaEnlazada<Letra> Partida::generarLetrasJugables(ListaEnlazada<Palabra> &diccionario) {
    Nodo<Palabra> *actual = diccionario.obtenerCabeza(); //obteniendo la primera lera

    srand(static_cast<unsigned int>(time(nullptr))); // semilla de aleatoriedad

    while (actual != nullptr) {
        //mientras sigan habiendo palabras en el diccionario
        const string &palabra = actual->dato.getContenido(); //obteniendo el contenido de la palabra

        for (char caracter: palabra) {
            //recorriendo cada letra de la palabra
            Letra letra; //creando objeto letra
            letra.setLetra(caracter); // asignando la letra
            letra.setPunteo(rand() % 9 + 1); // creando la puntuacion aleatoria dela letra

            letrasJugables.agregarFinal(letra); // agregando la letra a la lista
        }
        actual = actual->siguiente; // pasar al siguiente nodo del diccionario, para analizar la siguiente palabra
    }
    return letrasJugables;
}

void Partida::repartirLetras() {
    int cantidadJugadores = jugadores.contarElementos();
    if (cantidadJugadores == 0) return;
    Nodo<Letra> *actualLetra = letrasJugables.obtenerCabeza();

    // repartiendo hasta que no haya dato siguiente
    while (actualLetra != nullptr) {
        Jugador actualJugador = jugadores.desencolar(); // guardando jugador
        actualJugador.setLetra(actualLetra->dato); // dandole una ficha
        jugadores.encolar(actualJugador); // agregandolo a la cola nuevamente

        actualLetra = actualLetra->siguiente; // actualizando letra
    }
    Jugador jugadortmp = jugadores.obtenerFrente();
    jugadortmp.mostrarLetras();
    jugadortmp.ordenarLetrasPorPunteo();
    cout << "letras ordenadas: " << endl;
    jugadortmp.mostrarLetras();
}

// getters
Cola<Jugador> Partida::getColaJugadores() const { return jugadores; }
Pila<Palabra> Partida::getPilaPalabrasJugadas() const { return palabrasJugadas; }
ListaEnlazada<Jugador> Partida::getListaPunteos() const { return listaPunteos; }
ListaEnlazada<Palabra> Partida::getListaDiccionario() const { return diccionario; }
ListaEnlazada<Letra> Partida::getListaLetrasJugables() const { return letrasJugables; }

bool Partida::getHayPalabra() const { return hayPalabra; }

// setters
void Partida::setHayPalabra(bool nuevaHayPalabra) {
    hayPalabra = nuevaHayPalabra;
}
