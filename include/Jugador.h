//
// Created by ronyrojas on 19/02/25.
//

#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "ListaEnlazada.h"
#include "Letra.h"
using namespace std;

class Jugador
{
private:
    string nombre;
    int puntuacion;
    int cantidadTurnos;
    int tiempoJugado;
    ListaEnlazada<Letra> letras;

public:
    Jugador();

    //getters
    string getNombre() const;
    int getPuntuacion() const;
    int getCantidadTurnos() const;
    int getTiempoJugado() const;

    //setters
    void setNombre(string nuevoNombre);
    void setPuntuacion(int puntos);
    void aumentarTurno();
    void setTiempoJugado(int tiempoExtra);

};

#endif //JUGADOR_H
