//
// Created by ronyrojas on 19/02/25.
//
#include "../include/Letra.h"
#include <iostream>

using namespace std;

Letra::Letra()
{
    this->letra = "";
    this->punteo = 0;
}

// getters
string Letra::getLetra() const { return letra; }
int Letra::getPunteo() const { return punteo; }

//setters
void Letra::setLetra(string letra){
    this->letra = letra;
}

void Letra::setPunteo(int punteo){
    this->punteo = punteo;
}