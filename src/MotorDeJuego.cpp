//
// Created by ronyrojas on 19/02/25.
//
#include "../include/MotorDeJuego.h"


#include <iostream>
using namespace std;
MotorDeJuego::MotorDeJuego() {}

void MotorDeJuego::mostrarMenu()
{
    int opcion;

    do
    {
        cout << "            BIENVENIDO A SCRABBLE   " << endl;
        cout << "\n*********** Menu Principal ***********" << endl;
        cout << "1. Nueva Partida" << endl;
        cout << "2. Ver Reportes" << endl;
        cout << "3. Salir Del Juego" << endl;
        cout << "Selecciona Una Opcion" << endl;
        cin >> opcion;

        switch (opcion)
        {
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
        }
    } while (!finalizarEjecucion);
}

void MotorDeJuego::nuevaPartida()
{
    cout << "\n Iniciando Nueva Partida..." << endl;
}

void MotorDeJuego::verReportes()
{
    cout << "\n Mostrando Reportes..." << endl;
}