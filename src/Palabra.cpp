//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Palabra.h"
#include <iostream>

using namespace std;

Palabra::Palabra()
{
    this->contenido = "";
    this->puntuacion = 0;
    this->palabraFormada = false;
}

// getters
string Palabra::getContenido() const { return contenido; }
int Palabra::getPuntuacion() const { return puntuacion; }
bool Palabra::isPalabraFormada() const { return palabraFormada; }

// setters
void Palabra::setContenido(string contenido)
{
    this->contenido = contenido;
}

void Palabra::setPuntuacion(int puntuacion)
{
    this->puntuacion = puntuacion;
}

void Palabra::setPalabraFormada(bool palabraFormada)
{
    this->palabraFormada = palabraFormada;
}

// Definición del operador de salida
ostream& operator<<(ostream& os, const Palabra& palabra) {
    os << palabra.getContenido();
    return os;
}