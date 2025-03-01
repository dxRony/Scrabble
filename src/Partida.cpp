#include "../include/Partida.h"

#include "../include/Reporte.h"
using namespace std;

Partida::Partida() {
    jugadores = new Cola<Jugador>(); //cola de jugadores en la partida
    palabrasJugadas = new Pila<Palabra>(); //pila de palabras que se han completado en el tablero
    listaPunteos = new ListaEnlazada<Jugador>(); //lista de punteos de los jugadores
    letrasJugables = new ListaEnlazada<Letra>(); //lista de letras a repartir entre todos los jugadores
    diccionario = nullptr; //lista de palabras que se leeran del archivo
    hayPalabra = false; //bandera para verificar si se pueden formar palabras en el tablero
    hayLetraCentro = false; //bandera para ver si ya hay una letra en el centro
    partidaTerminada = false; //bandera que finaliza la ejecucion del juego
}

Partida::~Partida() {
    delete jugadores;
    delete palabrasJugadas;
    delete listaPunteos;
    delete letrasJugables;
}

void Partida::iniciarPartida(ListaEnlazada<Palabra> *diccionario) {
    this->diccionario = diccionario;
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
    } while (!partidaTerminada && !diccionario->isEmpty());
    cout << "Generando reportes..." << endl;
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

        Jugador nuevoJugador; // creando jugador
        nuevoJugador.setNombre(nombreJugador); //agregandole nombre
        jugadores->encolar2(nuevoJugador); // encolando al jugador
    }
    cout << "\nJugadores registrados\n" << endl;
}

void Partida::generarLetrasJugables() {
    if (diccionario == nullptr || diccionario->isEmpty()) {
        cout << "El diccionario no tiene palabras" << endl;
        return;
    }
    // recorriendo el diccionario
    for (int i = 0; i < diccionario->getTamano(); i++) {
        //obteniendo palabra por palabra del diccionario
        Palabra *palabraActual = diccionario->obtenerDatoEnPosicion(i);
        // guardando el contenido de la palabra
        string contenido = palabraActual->getContenido();
        // recorriendo letra por letra de la palabra
        for (char letraChar: contenido) {
            // creando un objeto Letra y dandole los respectivos valores
            Letra letra;
            letra.setLetra(letraChar); // asignando char letra
            letra.setPunteo(rand() % 9 + 1); // punteo aleatorio (1-9)
            // agregando letra preparada a la lista de letras jugables
            this->letrasJugables->insertar(letra);
        }
    }
}

void Partida::repartirLetras() {
    if (letrasJugables == nullptr || letrasJugables->isEmpty()) {
        cout << "No hay letras jugables para repartir" << endl;
        return;
    }
    if (jugadores == nullptr || jugadores->isVacio()) {
        cout << "No hay jugadores para repartir las letras." << endl;
        return;
    }

    // repartiendo letrasJugables entre jugadores, hasta vaciar letrasJugables
    while (!letrasJugables->isEmpty()) {
        // creando jugadorTemporal
        Jugador *jugadorActual = jugadores->desencolar();

        // eliminando la primera letra y guardandola en nodoLetra
        Nodo<Letra> *nodoLetra = letrasJugables->eliminarPorIndice(0);

        //obteniendo el dato del nodo
        Letra *letra = nodoLetra->getData();

        // guardando la letra en las letras del jugadorTemporal
        if (letra != nullptr) {
            jugadorActual->getLetras()->insertar2(letra); // Insertamos la letra en el jugador
        }
        delete nodoLetra;
        //devolviendo el jugadorTemporal a la cola
        jugadores->encolar(jugadorActual);
    }
}

void Partida::ordenarLetrasJugables() {
    if (jugadores == nullptr || jugadores->isVacio()) {
        cout << "No hay jugadores" << endl;
        return;
    }
    int numJugadores = jugadores->obtenerTamano();
    for (int i = 0; i < numJugadores; i++) {
        //recorriendo jugadores para aplicarles el metodo ordenarLetrasPorPunteo
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
    // desencolando al jugador
    jugadorActual = jugadores->desencolar2();
    //volviendolo a encolar para ciclarlo
    jugadores->encolar2(jugadorActual);
}

void Partida::realizarTurno(int opcionTurno) {
    bool turnoTerminado = false;

    while (!turnoTerminado) {
        switch (opcionTurno) {
            case 1: {
                cout << "Letras de " << jugadorActual.getNombre() << ":" << endl;
                jugadorActual.mostrarLetras();
                int indiceLetra;
                cout << "\nIngresa el indice de la letra que quieres colocar: " << endl;
                cin >> indiceLetra;
                if (indiceLetra < 0 || indiceLetra >= jugadorActual.getLetras()->getTamano()) {
                    cout << "indice no valido, intentalo de nuevo" << endl;
                    break;
                }
                Letra *letraSeleccionada = jugadorActual.getLetras()->obtenerDatoEnPosicion(indiceLetra - 1);
                int fila, columna;
                cout << "Ingresa la fila (1-15): ";
                cin >> fila;
                cout << "Ingresa la columna (1-15): ";
                cin >> columna;
                fila--;
                columna--;
                if (fila < 0 || fila >= 15 || columna < 0 || columna >= 15) {
                    cout << "posicion fuera del tablero :/" << endl;
                    break;
                }
                if (tableroDeJuego.obtenerLetra(fila, columna) != nullptr) {
                    cout << "La casilla ya esta ocupada, intentalo de nuevo." << endl;
                    break;
                }

                if (tableroDeJuego.colocarLetra(fila, columna, letraSeleccionada)) {
                    // si se coloca la letra del jugador en el tablero se elimina de sus letras
                    jugadorActual.getLetras()->eliminar2(indiceLetra - 1);
                    cout << "Letra colocada correctamente en: ("
                            << (fila + 1) << ", " << (columna + 1) << ")." << endl;
                    tableroDeJuego.imprimirTablero();
                    //cuando se coloca una letra se comprueba si en su fila o columna la letra existe en diccionario
                    comprobarLetraFormada(diccionario);
                    //sumandole 1 turno al jugador
                    jugadorActual.setCantidadTurnos(jugadorActual.getCantidadTurnos() + 1);
                    turnoTerminado = true;
                } else {
                    cout << "No se pudo colocar la letra, repite tu turno" << endl;
                }
                break;
            }
            case 2: {
                cout << "Letras de " << jugadorActual.getNombre() << ":" << endl;
                jugadorActual.mostrarLetras();
                opcionTurno = jugadorActual.mostrarOpcionesTurno();
                break;
            }
            case 3: {
                cout << "Palabras en el diccionario:" << endl;
                diccionario->imprimirLista();
                opcionTurno = jugadorActual.mostrarOpcionesTurno();
                break;
            }
            case 4: {
                cout << jugadorActual.getNombre() << " ha decidido pasar su turno" << endl;
                //sumandole 1 turno al jugador
                jugadorActual.setCantidadTurnos(jugadorActual.getCantidadTurnos() + 1);
                turnoTerminado = true;
                break;
            }
            case 5: {
                cout << "Finalizando partida..." << endl;
                partidaTerminada = true;
                //sumandole 1 turno al jugador
                jugadorActual.setCantidadTurnos(jugadorActual.getCantidadTurnos() + 1);
                turnoTerminado = true;
                break;
            }
            default: {
                cout << "opcion invalida, intenta de nuevo." << endl;
                opcionTurno = jugadorActual.mostrarOpcionesTurno();
                break;
            }
        }
    }
}

void Partida::comprobarLetraFormada(ListaEnlazada<Palabra> *diccionario) {
    // recorriendo diccionario por si alguna palabra es igual a las letras en el tablero
    for (int i = 0; i < diccionario->getTamano(); i++) {
        //guardando la palabra del diccionario y su contenido
        Palabra *palabraActual = diccionario->obtenerDatoEnPosicion(i);
        string palabra = palabraActual->getContenido();

        // llamando a metodo para ver si la palabra existe en el tablero
        if (tableroDeJuego.verificarPalabraTablero(palabra)) {
            // si la palbra existiera se recibe true y se procede a calcular el punteo de la palabra
            int puntuacionPalabra = 0;
            for (char letraChar: palabra) {
                // obteniendo cada letra obtener su punteo
                Letra *letra = tableroDeJuego.obtenerLetraTablero(letraChar);
                if (letra != nullptr) {
                    //validandoque la letra exista y agregando el punteo de la letra
                    puntuacionPalabra += letra->getPunteo();
                }
            }
            //mandando la puntuacion al jugador que formo la palabra
            jugadorActual.setPuntuacion(jugadorActual.getPuntuacion() + puntuacionPalabra);

            //eliminando la palabra del diccionario para que no se vuelva a encontrar en el futuro
            diccionario->eliminarPorIndice(i);

            // agregando la palabra para el reporte
            palabrasJugadas->push(*palabraActual);

            // Mostrar un mensaje indicando que se ha formado una palabra
            cout << "Has formado la palabra : " << palabra << "! Puntuacion obtendida: " << puntuacionPalabra << endl;
        }
    }
}

//getters
Pila<Palabra> *Partida::getPalabrasJugadas() {
    return palabrasJugadas;
}

ListaEnlazada<Palabra> *Partida::getDiccionario() {
    return diccionario;
}

Cola<Jugador> *Partida::getJugadores() {
    return jugadores;
}
