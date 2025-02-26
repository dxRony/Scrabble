//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Tablero.h"
#include <iostream>
#include <iomanip>

using namespace std;

Tablero::Tablero() {
    for (int i = 0; i < 15; i++) {
        // cada vez que se crea un tablero en partida se crea un tablero vacio
        for (int j = 0; j < 15; j++) {
            casillas[i][j]->setLetra(' ');
            casillas[i][j]->setPunteo(0);
        }
    }
    hayLetraCentro = false;
}

void Tablero::generarTablero() {
    srand(static_cast<unsigned int>(time(nullptr))); // Semilla para aleatoriedad
    int contador = 0;

    while (contador < 10) {
        // verificando que no se hayan creado las 10 casillas desactivadas
        int fila = rand() % 15; // coordenada aleatoria x
        int columna = rand() % 15; // coordenada aleatoria y

        if (casillas[fila][columna]->getLetra() == ' ' || fila == 7 && columna == 7) {
            // verificando que no haya * previo y que no se bloquee el espacio central
            casillas[fila][columna]->setLetra('*'); // insertando * (simbolizara que esta desactivada la casilla)
            contador++; // aumentando la cantidad de * en el tablero
        }
    }
}

bool Tablero::colocarLetra(Letra letra, int fila, int columna, ListaEnlazada<Palabra *> *diccionario) {
    int punteoLetra = letra.getPunteo();
    char contenidoLetra = letra.getLetra();
    bool colocada = false;

    if (fila < 0 || fila >= 15 || columna < 0 || columna >= 15) {
        cout << "Coordenadas a fuera del rango del tablero" << endl;
        colocada = false;
        return colocada;
    }

    if (!hayLetraCentro) {
        //reemplazando coordenadas cuando no haya letra en el centro
        cout << "La primera letra debe estar en el centro" << endl;
        fila = 7;
        columna = 7;
        cout << "Colocando letra en el centro " << endl;
        casillas[fila][columna]->setLetra(contenidoLetra);
        casillas[fila][columna]->setPunteo(punteoLetra);
        this->hayLetraCentro = true;
        colocada = true;
        return colocada;
    }
    //verificando que la casilla esta vacia
    if (casillas[fila][columna]->getLetra() != ' ') {
        cout << "La casilla ya esta ocupada. Has perdido tu turno :(" << endl;
        colocada = false;
        return colocada;
    }

    // verficando que la coordenada este a la par de otra letra (vertical u horizontal)
    bool letraContigua = false;
    if ((fila > 0 && casillas[fila - 1][columna]->getLetra() != ' ') ||
        (fila < 14 && casillas[fila + 1][columna]->getLetra() != ' ') ||
        (columna > 0 && casillas[fila][columna - 1]->getLetra() != ' ') ||
        (columna < 14 && casillas[fila][columna + 1]->getLetra() != ' ')) {
        //si las condiciones anteriores se cumplen, se puede colocar la letra en la coordenada
        letraContigua = true;
        cout << "Si se pudo jsjs " << endl;
    }
    if (!letraContigua) {
        cout << "Debiste colocar la letra juntoa otra letra. Has perdido tu turno :(" << endl;
        colocada = false;
        return colocada;
    }
    //despues de todas las validaciones ya se puede colocar la letra
    casillas[fila][columna]->setLetra(contenidoLetra);
    casillas[fila][columna]->setPunteo(punteoLetra);
    cout << "Letra: " << contenidoLetra << " colocada en (" << fila + 1 << "," << columna + 1 << ")" << endl;
    comprobarPalabraFormada(diccionario);
    return true;
}

void Tablero::comprobarPalabraFormada(ListaEnlazada<Palabra *> *diccionario) {
    /**
     * implementar la logica para verificar si se formo una palabra del diccionario
     */
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
        // linea de arriba
        cout << "    ";
        for (int col = 0; col < 15; col++) {
            cout << horizontal;
        }
        cout << "+\n";

        // imprimiendo valores del tablero
        cout << setw(2) << i + 1 << "  |";
        for (int j = 0; j < 15; j++) {
            cout << " " << casillas[i][j]->getLetra() << " |";
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

// getters
bool Tablero::getHayLetraCentro() const { return hayLetraCentro; }

//setters
void Tablero::setHayLetraCentro(bool hayLetra) { hayLetraCentro = hayLetra; }
