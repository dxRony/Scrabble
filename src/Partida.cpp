//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Partida.h"
#include "../include/Tablero.h"
#include <iostream>

using namespace std;

Partida::Partida() : jugadores(), palabrasJugadas(), listaPunteos(), diccionario(), letrasJugables() {
    this->hayPalabra = true;
    this->hayLetraCentro = false;
    this->jugadorActual = Jugador();
    this->tableroDeJuego = Tablero();
}

void Partida::iniciarPartida(ListaEnlazada<Palabra> diccionario) {
    this->diccionario = diccionario;
    this->registrarJugadores();
    jugadores = jugadores.mezclarCola();
    this->generarLetrasJugables(this->diccionario);
    //cout << "Letras a repartir entre los jugadores:" << endl;
    //letrasJugables.mostrarLista();
    cout << "Repartiendo letras (fichas) entre todos los jugadores y ordenandolas de mayor a menor punteo..." << endl;
    this->repartirLetras();
    this->ordenarLetrasJugadores();
    cout << "Generando turnos aleatorios..." << endl;
    cout << "Orden de los turnos para la partida: " << endl;
    jugadores.mostrarCola();
    cout << "Todo listo para iniciar..." << endl;
    tableroDeJuego.generarTablero(); //creando el tablero de juego
    cout << "El tablero para esta partida es:" << endl;
    tableroDeJuego.imprimirTablero();

    int opcionTurno=0;
    do {
        jugadorActual = this->cambiarTurno();
        opcionTurno = jugadorActual.mostrarOpcionesTurno();
        this->realizarTurno(opcionTurno);
        opcionTurno =0;
    } while (this->hayPalabra == false || this->diccionario.estaVacia());
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
}

void Partida::ordenarLetrasJugadores() {
    int cantidadJugadores = jugadores.contarElementos(); //obteniendo el numero de jugadores

    for (int i = 0; i < cantidadJugadores; ++i) {
        Jugador jugadorTmp = jugadores.obtenerFrente(); // obteniendo el frente de la cola
        jugadores.desencolar(); // desencolandolo

        jugadorTmp.ordenarLetrasPorPunteo(); // ordenando sus letras
        jugadores.encolar(jugadorTmp); // encolandolo con sus letras ordenadas
    }
}

Jugador Partida::cambiarTurno() {
    Jugador jugadorTmp = jugadores.obtenerFrente();
    jugadores.desencolar();
    jugadores.encolar(jugadorTmp);
    return jugadorTmp;
}

void Partida::realizarTurno(int opcionTurno) {
    int opcionTurno2 = 0;
    switch (opcionTurno) {
        case 1: //colocar letra
            int indiceLetra;
            int coordenadaY;
            int coordenadaX;
            Letra letraAColocar;

            cout << "Letras que tienes en tu bolsa:"<< endl;
            jugadorActual.mostrarLetras();            
            cout << "Ingresa el indice de la letra que quieres colocar:" << endl;
            cin >> indiceLetra;
            //letraAColocar = jugadorActual.getLetras().obtenerPorIndice(indiceLetra);
            cout << "Ingresa la coordenada Y donde quieres poner la letra:" << endl;
            cin >> coordenadaY;
            cout << "Ingresa la coordenada X donde quieres poner la letra:" << endl;
            cin >> coordenadaX;
            tableroDeJuego.colocarLetra(letraAColocar, coordenadaX + 1, coordenadaY + 1, diccionario);            

            break;
        case 2: //mostrar letras
            jugadorActual.mostrarLetras();
            opcionTurno2 = jugadorActual.mostrarOpcionesTurno();
            realizarTurno(opcionTurno2);

            break;
        case 3: //ver palabras jugables
            cout << "Letras que puedes formar: "<< endl;
            diccionario.mostrarLista();
            opcionTurno2 = jugadorActual.mostrarOpcionesTurno();
            realizarTurno(opcionTurno2);
        case 4: //pasar turno
                cout << "Turno saltado" << endl;
            break;
        default:
            cout << "Opcion ingresada no válida." << endl;
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
void Partida::setHayPalabra(bool nuevaHayPalabra) {
    hayPalabra = nuevaHayPalabra;
}
