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
    cout << "Generando turnos aleatorios..." << endl;
    jugadores->mezclarCola();
    jugadores->mostrarCola();
    cout << "Repartiendo letras a los jugadores y ordenandolas por puntuacion..." << endl;
    generarLetrasJugables();
    repartirLetras();
    ordenarLetrasJugables();
    cout << "Generando tablero con 10 casillas desactivadas..." << endl;
    tableroDeJuego.generarTablero();
    tableroDeJuego.imprimirTablero();


    do {
        cambiarTurno();
        int opcionTurno = jugadorActual.mostrarOpcionesTurno();
        cout << opcionTurno << endl;
        realizarTurno(opcionTurno);
    } while (hayPalabra || !diccionario->isEmpty());
    cout << "Se cumplio el while" << endl;
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

void Partida::cambiarTurno() {
    if (jugadores->isVacio()) {
        cout << "No hay jugadores en la cola." << endl;
        return;
    }

    // Desencolar al siguiente jugador
    jugadorActual = jugadores->desencolar2();

    // Mostrar el nombre del jugador actual
    cout << "\nTurno de: " << jugadorActual.getNombre() << endl;

    // Volver a encolar al jugador para mantener el orden de los turnos
    jugadores->encolar2(jugadorActual);
}

void Partida::realizarTurno(int opcionTurno) {
    bool turnoTerminado = false;

    while (!turnoTerminado) {
        switch (opcionTurno) {
            case 1: // Colocar una letra en el tablero
                cout << "Colocar letra en el tablero." << endl;

                tableroDeJuego.imprimirTablero();
                turnoTerminado = true; // El turno termina después de colocar una letra
                break;
            case 2: // Mostrar las letras del jugador actual
                cout << "Letras de " << jugadorActual.getNombre() << ":" << endl;
                jugadorActual.mostrarLetras();
            // El turno no termina, el jugador puede seleccionar otra opción
                opcionTurno = jugadorActual.mostrarOpcionesTurno();
                break;
            case 3: // Mostrar las palabras del diccionario
                cout << "Palabras en el diccionario:" << endl;
                diccionario->imprimirLista();
            // El turno no termina, el jugador puede seleccionar otra opción
                opcionTurno = jugadorActual.mostrarOpcionesTurno();
                break;
            case 4: // Pasar turno
                cout << jugadorActual.getNombre() << " ha decidido pasar su turno." << endl;
                turnoTerminado = true; // El turno termina sin realizar ninguna acción
                break;
            default: // Opción no válida
                cout << "Opción no válida. Intenta de nuevo." << endl;
            // El turno no termina, el jugador puede seleccionar otra opción
                opcionTurno = jugadorActual.mostrarOpcionesTurno();
                break;
        }
    }
}
