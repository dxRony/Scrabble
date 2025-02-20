//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Jugador.h"
#include <iostream>

using namespace std;

Jugador::Jugador(): letras()
{
    this->nombre = "";
    this->puntuacion = 0;
    this->cantidadTurnos = 0;
    this->tiempoJugado = 0;
}

// getters
string Jugador::getNombre() const { return nombre; }
int Jugador::getPuntuacion() const { return puntuacion; }
int Jugador::getCantidadTurnos() const { return cantidadTurnos; };
int Jugador::getTiempoJugado() const { return tiempoJugado; }
ListaEnlazada<Letra> Jugador::getLetras() const {
    return letras;
}


// setters
void Jugador::setNombre(string nuevoNombre)
{
    nombre = nuevoNombre;
}

void Jugador::setPuntuacion(int puntos)
{
    puntuacion = puntos;
}

void Jugador::setCantidadTurnos(int turnoExtra)
{
    cantidadTurnos = turnoExtra;
}

void Jugador::setTiempoJugado(int tiempoExtra)
{
    tiempoJugado = tiempoExtra;
}

void Jugador::setLetra(Letra letra) {
    letras.agregarFinal(letra);
}

ostream& operator<<(ostream& os, const Jugador& jugador) {
    os << "Nombre: " << jugador.getNombre()
       << ", Puntuación: " << jugador.getPuntuacion()
       << ", Turnos: " << jugador.getCantidadTurnos()
       << ", Tiempo Jugado: " << jugador.getTiempoJugado() << "s";
    return os;
}