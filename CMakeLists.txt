cmake_minimum_required(VERSION 3.30)
project(Scrabble)

set(CMAKE_CXX_STANDARD 11)

add_executable(Scrabble src/main.cpp
        include/MotorDeJuego.h
        src/MotorDeJuego.cpp
        include/Archivo.h
        src/Archivo.cpp
        include/ListaEnlazada.h
        include/Palabra.h
        src/Palabra.cpp
        include/Nodo.h
        include/Partida.h
        src/Partida.cpp
        include/Cola.h
        include/Pila.h
        include/Jugador.h
        src/Jugador.cpp
        include/Letra.h
        src/Letra.cpp
        include/Tablero.h
        src/Tablero.cpp
        include/Reporte.h
        src/Reporte.cpp)
