//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Partida.h"
#include "../include/Tablero.h"
#include "../include/Letra.h"
#include "../include/Palabra.h"
#include <iostream>
using namespace std;

Partida::Partida() {
    jugadores = new Cola<Jugador *>();
    palabrasJugadas = new Pila<Palabra *>();
    listaPunteos = new ListaEnlazada<Jugador *>();
    diccionario = new ListaEnlazada<Palabra *>();
    letrasJugables = new ListaEnlazada<Letra *>();
    hayPalabra = true;
    hayLetraCentro = false;
    jugadorActual = nullptr;
    tableroDeJuego = new Tablero();
}

Partida::~Partida() {
    delete jugadores;
    delete palabrasJugadas;
    delete listaPunteos;
    delete diccionario;
    delete letrasJugables;
    delete tableroDeJuego;
}

void Partida::iniciarPartida(ListaEnlazada<Palabra *> *diccionario) {
    this->diccionario = diccionario;
    registrarJugadores();
    jugadores->mezclarCola();
    generarLetrasJugables(diccionario);
    //cout << "Letras a repartir entre los jugadores:" << endl;
    //letrasJugables.mostrarLista();
    cout << "Repartiendo letras (fichas) entre todos los jugadores y ordenandolas de mayor a menor punteo..." << endl;
    repartirLetras();
    ordenarLetrasJugadores();
    cout << "Generando turnos aleatorios..." << endl;
    cout << "Orden de los turnos para la partida: " << endl;
    jugadores->mostrarCola();
    cout << "Todo listo para iniciar..." << endl;
    tableroDeJuego->generarTablero(); //creando el tablero de juego
    cout << "El tablero para esta partida es:" << endl;
    tableroDeJuego->imprimirTablero();

    int opcionTurno = 0;
    do {
        jugadorActual = cambiarTurno();
        opcionTurno = jugadorActual->mostrarOpcionesTurno();
        realizarTurno(opcionTurno);
        tableroDeJuego->imprimirTablero();
    } while (hayPalabra == true || this->diccionario->estaVacia());
    cout << "Se cumplio el while" << endl;
    //ciclando mientras hayan palabrasJugables o se puedan formar palabras
}

void Partida::registrarJugadores() {
    int cantidadJugadores = 0;
    cout << "\nIngresa el numero de jugadores que tendra la partida..." << endl;
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

        Jugador *jugador = new Jugador();
        jugador->setNombre(nombre);
        jugador->setPuntuacion(0);
        jugador->setCantidadTurnos(0);
        jugador->setTiempoJugado(0);
        jugadores->encolar(jugador);
    }
    cout << "Jugadores: " << endl;
    jugadores->mostrarCola();
}

ListaEnlazada<Letra *> *Partida::generarLetrasJugables(ListaEnlazada<Palabra *> *diccionario) {
    Nodo<Palabra *> *actual = diccionario->obtenerCabeza(); //obteniendo la primera lera

    srand(static_cast<unsigned int>(time(nullptr))); // semilla de aleatoriedad

    while (actual != nullptr) {
        //mientras sigan habiendo palabras en el diccionario
        for (char caracter: actual->dato->getContenido()) {
            //recorriendo cada letra de la palabra
            Letra *letra = new Letra(); //creando objeto letra
            letra->setLetra(caracter); // asignando la letra
            letra->setPunteo(rand() % 9 + 1); // creando la puntuacion aleatoria dela letra
            letrasJugables->agregarFinal(letra); // agregando la letra a la lista
        }
        actual = actual->siguiente; // pasar al siguiente nodo del diccionario, para analizar la siguiente palabra
    }
    return letrasJugables;
}

void Partida::repartirLetras() {
    int cantidadJugadores = jugadores->contarElementos();
    if (cantidadJugadores == 0) return;
    Nodo<Letra *> *actualLetra = letrasJugables->obtenerCabeza();
    // repartiendo hasta que no haya dato siguiente
    while (actualLetra != nullptr) {
        Jugador *actualJugador = jugadores->desencolar(); // guardando jugador
        actualJugador->setLetra(actualLetra->dato); // dandole una ficha
        jugadores->encolar(actualJugador); // agregandolo a la cola nuevamente
        actualLetra = actualLetra->siguiente; // actualizando letra
    }
}

void Partida::ordenarLetrasJugadores() {
    int cantidadJugadores = jugadores->contarElementos(); //obteniendo el numero de jugadores
    for (int i = 0; i < cantidadJugadores; ++i) {
        Jugador *jugadorTmp = jugadores->desencolar(); // obteniendo el frente de la cola
        jugadorTmp->ordenarLetrasPorPunteo(); // ordenando sus letras
        jugadores->encolar(jugadorTmp); // encolandolo con sus letras ordenadas
    }
}

Jugador *Partida::cambiarTurno() {
    Jugador *jugadorTmp = jugadores->desencolar();
    jugadores->encolar(jugadorTmp);
    return jugadorTmp;
}

void Partida::realizarTurno(int opcionTurno) {
    int opcionTurno2 = 0;
    switch (opcionTurno) {
        case 1: {
            //colocar letra
            int indiceLetra, columna, fila;
            cout << "Letras que tienes en tu bolsa:" << endl;
            jugadorActual->mostrarLetras();
            cout << "Ingresa el indice de la letra que quieres colocar:" << endl;
            cin >> indiceLetra;
            Letra letraAColocar = jugadorActual->getLetras()->obtenerYEliminar(indiceLetra - 1);
            //Letra* letraAColocar = jugadorActual->getLetras()->obtenerYEliminar(indiceLetra - 1);
            cout << "Ingresa la columna donde quieres poner la letra:" << endl;
            cin >> columna;
            cout << "Ingresa la fila donde quieres poner la letra:" << endl;
            cin >> fila;
            tableroDeJuego->colocarLetra(letraAColocar, fila - 1, columna - 1, diccionario);

            break;
        }
        case 2: {
            //mostrar letras
            jugadorActual->mostrarLetras();
            opcionTurno2 = jugadorActual->mostrarOpcionesTurno();
            realizarTurno(opcionTurno2);
            break;
        }
        case 3: {
            //ver palabras jugables
            cout << "Letras que puedes formar: " << endl;
            diccionario->mostrarLista();
            opcionTurno2 = jugadorActual->mostrarOpcionesTurno();
            realizarTurno(opcionTurno2);
            break;
        }
        default: {
            cout << "Opcion ingresada no válida." << endl;
            break;
        }
    }
}

// getters
Cola<Jugador *> *Partida::getColaJugadores() const { return jugadores; }
Pila<Palabra *> *Partida::getPilaPalabrasJugadas() const { return palabrasJugadas; }
ListaEnlazada<Jugador *> *Partida::getListaPunteos() const { return listaPunteos; }
ListaEnlazada<Palabra *> *Partida::getListaDiccionario() const { return diccionario; }
ListaEnlazada<Letra *> *Partida::getListaLetrasJugables() const { return letrasJugables; }

bool Partida::getHayPalabra() const { return hayPalabra; }
void Partida::setHayPalabra(bool valor) { hayPalabra = valor; }
