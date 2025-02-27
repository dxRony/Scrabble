//
// Created by ronyrojas on 26/02/25.
//

#include "../include/Tablero.h"
#include <iostream>
#include <iomanip>
using namespace std;


Tablero::Tablero() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            casillas[i][j] = nullptr;
        }
    }
    hayLetraCentro = false;
}

void Tablero::generarTablero() {
    int casillasBloqueadas = 0;
    while (casillasBloqueadas < 10) {
        int fila = rand() % 15; // Fila aleatoria entre 0 y 14
        int columna = rand() % 15; // Columna aleatoria entre 0 y 14

        // Verificar si la casilla ya está bloqueada o es el centro
        if (casillas[fila][columna] == nullptr && !(fila == 7 && columna == 7)) {
            // Crear una letra con el carácter '*' y puntuación 0
            Letra *letraBloqueada = new Letra();
            letraBloqueada->setLetra('*');
            letraBloqueada->setPunteo(0);

            // Bloquear la casilla
            casillas[fila][columna] = letraBloqueada;
            casillasBloqueadas++;
        }
    }
}

void Tablero::imprimirTablero() const{
    cout << "Tablero de juego:" << endl;

    // Imprimir la numeración de las columnas
    cout << "    "; // Espacio para alinear las columnas
    for (int col = 1; col <= 15; col++) {
        cout << " " << setw(2) << col << " "; // Mostrar números de columna
    }
    cout << endl;

    // Imprimir el borde superior del tablero
    cout << "    -"; // Espacio para alinear las filas o "    -"
    for (int col = 0; col < 15; col++) {
        cout << "----"; // Borde superior de cada columna
    }
    cout << endl;

    // Imprimir las filas del tablero
    for (int fila = 0; fila < 15; fila++) {
        // Mostrar el número de fila
        cout << setw(2) << (fila + 1) << " |"; // Número de fila y borde izquierdo

        // Mostrar el contenido de cada casilla
        for (int col = 0; col < 15; col++) {
            if (casillas[fila][col] == nullptr) {
                cout << "   |"; // Casilla vacía
            } else {
                cout << " " << casillas[fila][col]->getLetra() << " |"; // Mostrar la letra
            }
        }
        cout << endl;

        // Imprimir el borde inferior de la fila
        cout << "    -"; // Espacio para alinear las filas
        for (int col = 0; col < 15; col++) {
            cout << "----"; // Borde inferior de cada columna
        }
        cout << endl;
    }
}


