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
    cout  << "Generando turnos aleatorios..." << endl;
    jugadores = jugadores.mezclarCola();
    jugadores.mostrarCola();
    this->generarLetrasJugables(diccionario);
    cout << "Letras jugables a repartir entre los jugadores:" << endl;
    letrasJugables.mostrarLista();
    cout << "Repartiendo letras (fichas) entre todos los jugadores..." << endl;
}

void Partida::registrarJugadores() {
    int cantidadJugadores = 0;
    cout << "Ingresa el numero de jugadores que tendra la partida..." << endl;
    cin >> cantidadJugadores;

    while (cantidadJugadores <2) {
        cout << "Debe haber minimo 2 jugadores en la partida" << endl;
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
        jugadores.encolar(jugador);  // encolando al jugador
    }
    cout << "Jugadores: " << endl;
    jugadores.mostrarCola();
}

ListaEnlazada<Letra> Partida::generarLetrasJugables(ListaEnlazada<Palabra>& diccionario) {
    Nodo<Palabra>* actual = diccionario.obtenerCabeza();    //obteniendo la primera lera

    srand(static_cast<unsigned int>(time(nullptr))); // semilla de aleatoriedad

    while (actual != nullptr) {     //mientras sigan habiendo palabras en el diccionario
        const string& palabra = actual->dato.getContenido();    //obteniendo el contenido de la palabra

        for (char caracter : palabra) {     //recorriendo cada letra de la palabra
            Letra letra;                    //creando objeto letra
            letra.setLetra(caracter);       // asignando la letra
            letra.setPunteo(rand() % 9 + 1); // creando la puntuacion aleatoria dela letra

            letrasJugables.agregarFinal(letra); // agregando la letra a la lista
        }
        actual = actual->siguiente; // pasar al siguiente nodo del diccionario, para analizar la siguiente palabra
    }
    return letrasJugables;
}

void Partida::repartirLetras() {
    int cantidadJugadores = 0;
    Nodo<Jugador>* actualJugador = jugadores.obtenerFrente();   //obteniendo al primer jugador de la cola

    // Contar el número de jugadores
    while (actualJugador != nullptr) {
        cantidadJugadores++;
        actualJugador = actualJugador->siguiente;
    }

    if (cantidadJugadores == 0) return; // Si no hay jugadores, no se reparte

    Nodo<Letra>* actualLetra = letrasJugables.obtenerCabeza();
    actualJugador = jugadores.obtenerFrente();

    // Repartir letras de forma circular entre los jugadores
    while (actualLetra != nullptr) {
        actualJugador->dato.setLetra(actualLetra->dato); // Método de Jugador para recibir letras
        actualLetra = actualLetra->siguiente;
        actualJugador = actualJugador->siguiente ? actualJugador->siguiente : jugadores.obtenerFrente();
    }
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




