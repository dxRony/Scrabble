//
// Created by ronyrojas on 19/02/25.
//

#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "ListaEnlazada.h"
#include "Letra.h"
using namespace std;

class Jugador {
private:
    string nombre;
    int puntuacion;
    int cantidadTurnos;
    int tiempoJugado;
    ListaEnlazada<Letra> letras;

    //funciones privadas
    Nodo<Letra> *mergeSort(Nodo<Letra> *cabeza);

    Nodo<Letra> *dividirLista(Nodo<Letra> *cabeza);

    Nodo<Letra> *fusionarListas(Nodo<Letra> *izquierda, Nodo<Letra> *derecha);

public:
    Jugador();

    void mostrarLetras() const;

    void ordenarLetrasPorPunteo();


    //getters
    string getNombre() const;

    int getPuntuacion() const;

    int getCantidadTurnos() const;

    int getTiempoJugado() const;

    ListaEnlazada<Letra> getLetras() const;


    //setters
    void setNombre(string nuevoNombre);

    void setPuntuacion(int puntos);

    void setCantidadTurnos(int turnoExtra);

    void setTiempoJugado(int tiempoExtra);

    void setLetra(Letra letra);

    // Sobrecarga del operador <<
    friend ostream &operator<<(ostream &os, const Jugador &jugador);
};

#endif //JUGADOR_H
