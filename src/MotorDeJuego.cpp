//
// Created by ronyrojas on 19/02/25.
//
#include "../include/MotorDeJuego.h"


#include <iostream>

#include "../include/Archivo.h"
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
        cout << "Selecciona Una Opcion" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                nuevaPartida();
                break;
            case 2:
                verReportes();
                break;
            case 3:
                finalizarEjecucion = true;
            default:
                cout << "Opcion ingresada no válida." << endl;
            break;
        }
    } while (!finalizarEjecucion);
}

void MotorDeJuego::nuevaPartida() {
    cout << "\nIniciando Nueva Partida..." << endl;
    Archivo archivo;
    cout << "\nLeyendo y ordenando palabras..." << endl;
    ListaEnlazada<Palabra> *listaPalabras= archivo.ordenarAlfabeticamente();
    cout << "Lista de palabras disponibles para la partida:" << endl;
    listaPalabras->mostrarLista();
    cout << "creando partida..." << endl;
    Partida partida;
    cout << "creando instancia partida..." << endl;
    partida.iniciarPartida(listaPalabras);
}

void MotorDeJuego::verReportes() {
    cout << "\nMostrando Reportes..." << endl;
}
