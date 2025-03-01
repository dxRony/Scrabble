#include "../include/MotorDeJuego.h"
#include <iostream>
#include <limits>
#include "../include/Archivo.h"
#include "../include/Partida.h"
#include  "../include/Reporte.h"

using namespace std;

MotorDeJuego::MotorDeJuego() {
}

void MotorDeJuego::mostrarMenu() {
    int opcion;
    do {
        cout << "            BIENVENIDO A SCRABBLE   " << endl;
        cout << "\n*********** Menu Principal ***********" << endl;
        cout << "1. Nueva Partida" << endl;
        cout << "2. Ver Reportes" << endl;
        cout << "3. Salir Del Juego" << endl;
        cout << "Selecciona Una Opcion: ";

        try {
            cin >> opcion;
            //viendo si la entrada es un numero
            if (cin.fail()) {
                throw runtime_error("Entrada invalida, debes ingresar un numero entre 1 y 3");
            }
            //viendo si la entrada es un numero en el rango permitido
            if (opcion < 1 || opcion > 3) {
                throw out_of_range("Opcion fuera de rango, debes ingresar un numero entre 1 y 3");
            }
            switch (opcion) {
                case 1:
                    nuevaPartida();
                    break;
                case 2:
                    verReportes();
                    break;
                case 3:
                    finalizarEjecucion = true;
                    break;
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear(); // limpiando entrada en consola
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignorando entrada incorrecta
        }
    } while (!finalizarEjecucion);
}

void MotorDeJuego::nuevaPartida() {
    cout << "\nIniciando Nueva Partida..." << endl;
    Archivo archivo;
    cout << "\nLeyendo y ordenando palabras..." << endl;
    ListaEnlazada<Palabra> *listaPalabras = archivo.ordenarAlfabeticamente();
    cout << "Lista de palabras disponibles para la partida:" << endl;
    listaPalabras->imprimirLista();
    //iniciando partida
    Partida partida;
    partida.iniciarPartida(listaPalabras);
    //obteniendo atributos de la partida que ya ha finalizado
    reporte.actualizarReportes(partida.getPalabrasJugadas(), partida.getDiccionario(), partida.getJugadores());
}

void MotorDeJuego::verReportes() {
    //cout << "\nMostrando Reportes..." << endl;
    int opcion;
    do {
        cout << "\n*********** Menu de Reportes ***********" << endl;
        cout << "1. Historial de palabras jugadas" << endl;
        cout << "2. Historial de palabras no encontradas" << endl;
        cout << "3. Lista de Jugadores ordenada por puntaje" << endl;
        cout << "4. Regresar al menu principal" << endl;
        cout << "Selecciona una opcion: ";

        try {
            cin >> opcion;
            if (cin.fail()) {
                throw runtime_error("Entrada invalida, debes ingresar un numero (1-4)");
            }
            if (opcion < 1 || opcion > 4) {
                throw out_of_range("Opcion fuera de rango, debes ingresar un numero (1-4)");
            }
            switch (opcion) {
                case 1:
                    reporte.mostrarPalabrasEncontradas();
                    break;
                case 2:
                    reporte.mostrarPalabrasPerdidas();
                    break;
                case 3:
                    reporte.mostrarListaJugadores();
                    break;
                case 4:
                    cout << "Regresando al menu principal..." << endl;
                    break;
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opcion != 4);
}
