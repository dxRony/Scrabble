//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Tablero.h"
#include <iostream>

using namespace std;

Tablero::Tablero() {
    this->filas = 15;
    this->columnas = 15;
    this->espacioActivo = true;
}

// getters
int Tablero::getFilas() const { return filas; }
int Tablero::getColumnas() const { return columnas; }
bool Tablero::getEspacioActivo() const { return espacioActivo; }

// setters
void Tablero::setFilas(int filas) {
    this->filas = filas;
}

void Tablero::setColummnas(int columnas) {
    this->columnas = columnas;
}

void Tablero::setEspacioActivo(bool espacioActivo) {
    this->espacioActivo = espacioActivo;
}
