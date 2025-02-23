//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Tablero.h"
#include <iostream>
#include <iomanip>

using namespace std;

Tablero::Tablero() {
    for (int i = 0; i < 15; i++) {
        //cada vez que se crea un tablero en partida se crea un tablero vacio
        for (int j = 0; j < 15; j++) {
            casillas[i][j].setLetra(' ');
            casillas[i][j].setPunteo(0);
        }
    }
}

void Tablero::generarTablero() {
    srand(static_cast<unsigned int>(time(nullptr))); // Semilla para aleatoriedad
    int contador = 0;

    while (contador < 10) {
        //verificando que no se hayan creado las 10 casillas desactivadas
        int fila = rand() % 15; //coordenada aleatoria x
        int columna = rand() % 15; // coordenada aleatoria y

        if (casillas[fila][columna].getLetra() == ' ' || fila == 7 && columna == 7) {
            //verificando que no haya * previo y que no se bloquee el espacio central
            casillas[fila][columna].setLetra('*'); // insertando * (simbolizara que esta desactivada la casilla
            contador++; //aumentando la cantidad de * en el tablero
        }
    }
}

void Tablero::imprimirTablero() const {
    const string horizontal = "----"; // linea horizontal para cada letra

    // numeracion de las columnas
    cout << "    ";
    for (int col = 0; col < 15; col++) {
        cout << setw(3) << col + 1 << " "; // numero de cada columna -> setw(3) añadiendo 3 columnas de ancho
    }
    cout << "\n";

    for (int i = 0; i < 15; i++) {
        //linea de arriba
        cout << "    ";
        for (int col = 0; col < 15; col++) {
            cout << horizontal;
        }
        cout << "+\n";

        // imprimiendo valores del tablero
        cout << setw(2) << i + 1 << "  |";
        for (int j = 0; j < 15; j++) {
            cout << " " << casillas[i][j].getLetra() << " |";
        }
        cout << "\n";
    }

    // linea de abajo
    cout << "    ";
    for (int col = 0; col < 15; col++) {
        cout << horizontal;
    }
    cout << "\n";
}
