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
   delete jugadores;
    delete palabrasJugadas;
    delete listaPunteos;
    delete letrasJugables;
}

void Partida::iniciarPartida(ListaEnlazada<Palabra> *diccionario) {
    this->diccionario = diccionario;
    cout << "\nDiccionario recibido y asignado a la partida." << endl;
    cout << "Palabras en el diccionario:" << endl;
    diccionario->imprimirLista();
    agregarJugadores();
    cout << "Revolviendo turnos..." << endl;
    jugadores->mezclarCola();
    jugadores->mostrarCola();
    cout << "Repartiendo letras a los jugadores..."<< endl;
    generarLetrasJugables();
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
}

void Partida::generarLetrasJugables() {
    // Verificamos que el diccionario no esté vacío
    if (diccionario == nullptr || diccionario->isEmpty()) {
        cout << "El diccionario está vacío." << endl;
        return;
    }

    // Recorremos cada palabra en el diccionario
    for (int i = 0; i < diccionario->obtenerTamano(); i++) {
        Palabra *palabraActual = diccionario->obtenerDatoEnPosicion(i);

        // Obtenemos el contenido de la palabra (string)
        string contenido = palabraActual->getContenido();

        // Recorremos cada letra del contenido
        for (char letraChar : contenido) {
            // Creamos un objeto Letra con la letra y un puntaje aleatorio
            Letra *letra = new Letra();
            letra->setLetra(letraChar) ; // Asignamos la letra
            letra->setPunteo(rand() % 9 + 1)  ; // Puntaje aleatorio entre 1 y 9

            // Agregamos la letra a la lista de letras jugables
            this->letrasJugables->insertar(letra);
        }
    }
    cout << "Letras jugables generadas." << std::endl;
}


