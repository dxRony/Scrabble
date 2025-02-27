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

void Tablero::imprimirTablero() const {
    cout << "**********TABLERO DE JUEGO**********" << endl;

    // Imprimir la numeración de las columnas
    cout << "    "; // Espacio para alinear las columnas
    for (int col = 1; col <= 15; col++) {
        cout << " " << setw(2) << col << " "; // Mostrar números de columna
    }
    cout << endl;

    // Imprimir el borde superior del tablero
    cout << "    -"; // Espacio para alinear las filas
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

Letra *Tablero::obtenerLetra(int fila, int columna) const {
    if (fila < 0 || fila >= 15 || columna < 0 || columna >= 15) {
        return nullptr; // Fuera del tablero
    }
    return casillas[fila][columna];
}

bool Tablero::colocarLetra(int fila, int columna, Letra *letraAColocar) {
    if (fila < 0 || fila >= 15 || columna < 0 || columna >= 15) {
        return false; // Fuera del tablero
    }
    if (casillas[fila][columna] != nullptr) {
        return false; // Casilla ocupada
    }
    if (!hayLetraCentro) {
        //reemplazando coordenadas cuando no haya letra en el centro
        cout << "\nLa primera letra debe estar en el centro" << endl;
        fila = 7;
        columna = 7;
        cout << "Colocando letra en el centro " << endl;
        hayLetraCentro = true;
    } else {
        //si ya hay letra en el centro
        // Validando que la letra este al lado de otra letra
        bool letraContigua = false;

        // Verificando arriba
        if (fila > 0 && casillas[fila - 1][columna] != nullptr) {
            letraContigua = true;
        }
        // Verificando abajo
        else if (fila < 14 && casillas[fila + 1][columna] != nullptr) {
            letraContigua = true;
        }
        // Verificando izquierda
        else if (columna > 0 && casillas[fila][columna - 1] != nullptr) {
            letraContigua = true;
        }
        // Verificando derecha
        else if (columna < 14 && casillas[fila][columna + 1] != nullptr) {
            letraContigua = true;
        }

        if (!letraContigua) {
            cout << "La letra debe colocarse al lado de otra letra ya colocada." << endl;
            return false;
        }
    }
    casillas[fila][columna] = letraAColocar;
    return true;
}

bool Tablero::verificarPalabraTablero(const string &palabra) {
    // recorriendo todo el tablero para ver si se formo la palabra del diccionario
    for (int fila = 0; fila < 15; fila++) {
        for (int columna = 0; columna < 15; columna++) {
            //lamando a metodo verificarPalabra desde la posicion actual
            if (verificarPalabraFormada(fila, columna, palabra)) {
                //devolviendo true a partida, para indicar que si se formo la palabra completa
                return true;
            }
        }
    }
    //devolviendo true o false segun lo obtenido del recorrido
    return false;
}

bool Tablero::verificarPalabraFormada(int fila, int columna, const string &palabra) {
    //entrando con la posicion actual y la palabra del diccionario

    //evaluando horizontalmente y manejando el espacio del tablero
    if (columna + palabra.length() <= 15) {
        bool coincide = true;
        for (int i = 0; i < palabra.length(); i++) {
            //obteniendo la letra del posicion actual
            Letra *letra = casillas[fila][columna + i];
            if (letra == nullptr || letra->getLetra() != palabra[i]) {
                //si la letra no coincide con la palabra o no hay letra en la posicion, se finaliza el ciclo y se devuelve false
                coincide = false;
                break;
            }
        }
        if (coincide) {
            //si coincide, se devuelve true, para avanzar a la siguiente letra
            return true;
        }
    }

    //evaluando verticalmente y manejando el espacio del tablero
    if (fila + palabra.length() <= 15) {
        bool coincide = true;
        for (int i = 0; i < palabra.length(); i++) {
            Letra *letra = casillas[fila + i][columna];
            if (letra == nullptr || letra->getLetra() != palabra[i]) {
                coincide = false;
                break;
            }
        }
        if (coincide) {
            return true;
        }
    }
    //devolviendo true si se formo una fracion de la palabra, y avanzar al resto de la palabra
    return false;
}

Letra *Tablero::obtenerLetraTablero(char letraChar) {
    //recorriend el tablero en busqueda de la letra que forma la palabra formada
    for (int fila = 0; fila < 15; fila++) {
        for (int columna = 0; columna < 15; columna++) {
            Letra *letra = casillas[fila][columna];//obteniendo la letra de la posicion y devolviendola
            if (letra != nullptr && letra->getLetra() == letraChar) {
                return letra;
            }
        }
    }
    return nullptr;
}
