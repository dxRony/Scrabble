#include "../include/Tablero.h"
#include <iostream>
#include <iomanip>
using namespace std;

Tablero::Tablero() {
    //iniciando tablero con nullptr
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
        int fila = rand() % 15; // fila aleatoria (0-14)
        int columna = rand() % 15; // columna aleatoria (0-14)

        // verificando si la casilla ya esta bloqueada o esta en el centro donde estara la primer letra
        if (casillas[fila][columna] == nullptr && !(fila == 7 && columna == 7)) {
            // creando letra con contenido * y puntuación 0
            Letra *letraBloqueada = new Letra();
            letraBloqueada->setLetra('*');
            letraBloqueada->setPunteo(0);
            // bloqueando la casilla
            casillas[fila][columna] = letraBloqueada;
            casillasBloqueadas++;
        }
    }
}

void Tablero::imprimirTablero() const {
    cout << "**********TABLERO DE JUEGO**********" << endl;

    // numeracion de las columnas
    cout << "    "; // alineacion de columnas
    for (int col = 1; col <= 15; col++) {
        cout << " " << setw(2) << col << " ";
    }
    cout << endl;
    // birde superior
    cout << "    -"; // alineacion de filas
    for (int col = 0; col < 15; col++) {
        cout << "----"; // borde superior de cada columna
    }
    cout << endl;
    // imprimiendo filas
    for (int fila = 0; fila < 15; fila++) {
        // Mostrar el número de fila
        cout << setw(2) << (fila + 1) << " |"; // num fila y borde izq
        // mostrando letra de cada casilla
        for (int col = 0; col < 15; col++) {
            if (casillas[fila][col] == nullptr) {
                cout << "   |"; //si hay casilla vacia se muestra el espacio en blanco
            } else {
                cout << " " << casillas[fila][col]->getLetra() << " |"; // sino se muestra la letra
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
        return nullptr;
    }
    //devolviendo letra del tablero en la posicion indicada
    return casillas[fila][columna];
}

bool Tablero::colocarLetra(int fila, int columna, Letra *letraAColocar) {
    if (fila < 0 || fila >= 15 || columna < 0 || columna >= 15) {
        return false;
    }
    if (casillas[fila][columna] != nullptr) {
        //verificando si la casilla ya esta ocupada
        return false;
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

        // viendo que haya letra arriba
        if (fila > 0 && casillas[fila - 1][columna] != nullptr) {
            letraContigua = true;
        }
        // viendo que haya letra abajo
        else if (fila < 14 && casillas[fila + 1][columna] != nullptr) {
            letraContigua = true;
        }
        // viendo que haya letra izquierda
        else if (columna > 0 && casillas[fila][columna - 1] != nullptr) {
            letraContigua = true;
        }
        // viendo que haya letra derecha
        else if (columna < 14 && casillas[fila][columna + 1] != nullptr) {
            letraContigua = true;
        }
        if (!letraContigua) {
            //si no hay letra a la par
            cout << "La letra debe colocarse al lado de otra letra ya colocada." << endl;
            return false;
        }
    }
    casillas[fila][columna] = letraAColocar;
    return true;
}

bool Tablero::verificarPalabraTablero(const string &palabra) const {
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

bool Tablero::verificarPalabraFormada(int fila, int columna, const string &palabra) const {
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

Letra *Tablero::obtenerLetraTablero(char letraChar) const {
    //recorriend el tablero en busqueda de la letra que forma la palabra formada
    for (int fila = 0; fila < 15; fila++) {
        for (int columna = 0; columna < 15; columna++) {
            Letra *letra = casillas[fila][columna]; //obteniendo la letra de la posicion y devolviendola
            if (letra != nullptr && letra->getLetra() == letraChar) {
                return letra;
            }
        }
    }
    return nullptr;
}
