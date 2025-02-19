cmake_minimum_required(VERSION 3.30)
project(Scrabble)

set(CMAKE_CXX_STANDARD 11)

add_executable(Scrabble main.cpp
        include/MotorDeJuego.h
        src/MotorDeJuego.cpp
        include/Archivo.h
        include/Cola.h
        include/Jugador.h
        include/Letra.h
        include/ListaEnlazada.h
        include/Palabra.h
        include/Partida.h
        include/Pila.h
        include/Reporte.h
        include/Tablero.h
        src/Archivo.cpp
        src/Jugador.cpp
        src/Letra.cpp
        src/Palabra.cpp
        src/Partida.cpp
        src/Reporte.cpp
        src/Tablero.cpp)
