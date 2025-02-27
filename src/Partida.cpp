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
    cout << "Repartiendo letras a los jugadores y ordenandolas por puntuacion..." << endl;
    generarLetrasJugables();
    repartirLetras();
    ordenarLetrasJugables();
}

void Partida::agregarJugadores() {
    int cantidadJugadores;
    cout << "\nIngrese la cantidad de jugadores: ";
    cin >> cantidadJugadores;

    while (cantidadJugadores < 2) {
        cout << "Debe haber al menos 2 jugadores, intentalo nuevamente: ";
        cin >> cantidadJugadores;
    }

    for (int i = 1; i <= cantidadJugadores; i++) {
        string nombreJugador;
        cout << "Ingrese el nombre del jugador " << i << ": ";
        cin >> nombreJugador;

        Jugador nuevoJugador; // Jugador creado dinámicamente
        nuevoJugador.setNombre(nombreJugador); // Uso de puntero
        jugadores->encolar2(nuevoJugador); // Se pasa Jugador* como argumento
    }

    cout << "\nJugadores registrados.\n" << endl;
}

void Partida::generarLetrasJugables() {
    // Verificamos que el diccionario no esté vacío
    if (diccionario == nullptr || diccionario->isEmpty()) {
        cout << "El diccionario está vacío." << endl;
        return;
    }

    // Recorremos cada palabra en el diccionario
    for (int i = 0; i < diccionario->getSize(); i++) {
        Palabra *palabraActual = diccionario->obtenerDatoEnPosicion(i);

        // Obtenemos el contenido de la palabra (string)
        string contenido = palabraActual->getContenido();

        // Recorremos cada letra del contenido
        for (char letraChar: contenido) {
            // Creamos un objeto Letra con la letra y un puntaje aleatorio
            Letra letra; // Objeto Letra (no puntero)
            letra.setLetra(letraChar); // Asignamos la letra
            letra.setPunteo(rand() % 9 + 1); // Puntaje aleatorio entre 1 y 9

            // Agregamos la letra a la lista de letras jugables
            this->letrasJugables->insertar(letra);
        }
    }
}

void Partida::repartirLetras() {
    // Verificamos que haya letras jugables y jugadores
    if (letrasJugables == nullptr || letrasJugables->isEmpty()) {
        cout << "No hay letras jugables para repartir." << endl;
        return;
    }
    if (jugadores == nullptr || jugadores->isVacio()) {
        cout << "No hay jugadores para repartir las letras." << endl;
        return;
    }

    // Repartimos las letras hasta que se acaben
    while (!letrasJugables->isEmpty()) {
        // Desencolamos al jugador actual
        Jugador *jugadorActual = jugadores->desencolar();

        // Eliminamos la primera letra de la lista y obtenemos el nodo
        Nodo<Letra> *nodoLetra = letrasJugables->eliminar(0);

        // Obtenemos el dato (Letra*) del nodo
        Letra *letra = nodoLetra->getData();

        // Asignamos la letra al jugador actual
        if (letra != nullptr) {
            jugadorActual->getLetras()->insertar2(letra); // Insertamos la letra en el jugador
        }

        // Liberamos el nodo (pero no el dato, ya que ahora pertenece al jugador)
        delete nodoLetra;

        // Volvemos a encolar al jugador para mantener el orden
        jugadores->encolar(jugadorActual);
    }
}

void Partida::ordenarLetrasJugables() {
    if (jugadores == nullptr || jugadores->isVacio()) {
        cout << "No hay jugadores" << endl;
        return;
    }
    // Recorrer la cola de jugadores
    int numJugadores = jugadores->obtenerTamano();
    for (int i = 0; i < numJugadores; i++) {
        Jugador *jugadorActual = jugadores->desencolar();
        jugadorActual->ordenarLetrasPorPunteo(); // Ordenar las letras del jugador
        jugadores->encolar(jugadorActual); // Volver a encolar al jugador
    }
}
